#include "Game.h"
#include "Config.h"

Game::Game() {
    currentStatus = GameState::PLAYING;

	lastAnswer = -1;

    texLoco = {0};
    texVagon = {0};
    texFondo = {0};
    texVia = {0};
    texSalida = {0};
    texLlegada = {0};

    rectLlegada = { 0 };
}

void Game::Inits() {
    InitWindow(screenWidth, screenHeight, "Tren Radioactivo - UNL");

    SetTargetFPS(60);

    // Carga de texturas
    texLoco = LoadTexture("assets/locomotora.png");
    texVagon = LoadTexture("assets/vagon.png");
    texFondo = LoadTexture("assets/fondo.png");
    texVia = LoadTexture("assets/via.png");
	texSalida = LoadTexture("assets/salida.png");
	texLlegada = LoadTexture("assets/llegada.png");

	rectLlegada = { (float)screenWidth - texLlegada.width, (float)SPACE_BETWEEN_TRACKS * 3 - texLlegada.height, (float)texLlegada.width, (float)texLlegada.height };

    map.Init(texFondo, texVia);
    train.Init(texLoco, texVagon);

    for (int carril = 1; carril < 4; carril++) {
        float yPos = SPACE_BETWEEN_TRACKS * carril - texVagon.height;

        for (int i = 0; i < 2; i++) {
            // Posición X aleatoria entre 200 y el ancho de pantalla - 100
            float xPos = (float)GetRandomValue(200, screenWidth - 100);
            TrainCar* nuevoSuelto = new TrainCar({ xPos, yPos }, texVagon, 0);
            vagonesSueltos.push_back(nuevoSuelto);
        }
    }

    ecuacion.GenerateAgain();
}
void Game::CheckCollider() {
	//variables para facilitar la escritura
	Rectangle rectLoco = { train.GetPHeadPos().x, train.GetPHeadPos().y, (float)texLoco.width, (float)texLoco.height };
    float yLlegada = (SPACE_BETWEEN_TRACKS * 3) - (texLlegada.height);
    Rectangle rectLlegada = { (float)screenWidth - texLlegada.width, yLlegada, (float)texLlegada.width, (float)texLlegada.height };

    DrawRectangleLines(rectLlegada.x, rectLlegada.y, rectLlegada.width, rectLlegada.height, RED);
	
    // para poder borrar el vagon del vector si chocamos
    for (auto it = vagonesSueltos.begin(); it != vagonesSueltos.end(); ++it) {
        if (CheckCollisionRecs(rectLoco, (*it)->GetRec())) {
            if (currentStatus == GameState::PLAYING) {
                traincarActualCollided = *it; // Guardo la referencia

                // Quito el vagon de la lista de "sueltos" para que no se dibuje mas
                vagonesSueltos.erase(it);

                // Disparo la ecuacion
                currentStatus = GameState::WAITING_RTA;
                askTimer.Start(ASK_TIME_LIMIT);
                hud.ResetInput();
                break; // Salimos del bucle
            }
        }
    }

    if (CheckCollisionRecs(rectLoco, rectLlegada)) {
        if (vagonesSueltos.empty()) { // Solo gana si no quedan vagones en el mapa
            currentStatus = GameState::VICTORI;
        }
    }
}

void Game::Run() {
    //flujo del juego
    float dt = GetFrameTime();
    Draw();
	//estados del juego
    switch (currentStatus) {
    case GameState::PLAYING: 
        train.Update(dt);
        map.Update();
        CheckCollider();
        break;

    case GameState::WAITING_RTA:
    {
        askTimer.Update();
        map.Update();
        // Obtenemos la respuesta del teclado numerico del HUD
        int answer = hud.ActualizarTeclado(askTimer.tiempoRestante);

        if (answer != -1) {
			lastAnswer = answer; //la uso para mostrar el numero en el vagon que se une al tren si la respuesta es correcta
            CheckAnswer(answer);
        }

        if (askTimer.TimeIsUp()) {
            // Si se acaba el tiempo, pierde un vagon
            train.RemoveLast();
            ecuacion.GenerateAgain();
            currentStatus = GameState::PLAYING;
        }
    }
        break;

    case GameState::GAMEOVER: 
        if (IsKeyPressed(KEY_R)){ 
            Inits(); 
			currentStatus = GameState::PLAYING;
        } // Reiniciar
   
        break;
	case GameState::VICTORI:
        if (IsKeyPressed(KEY_R)) {
            train = Train();
            Inits();
            currentStatus = GameState::PLAYING;
        } // Reiniciar
    }


    
}

void Game::CheckAnswer(int rta) {
    if (ecuacion.Check(rta)) {
		//El vagon con el que chocamos se une al tren si la respuesta es correcta
        train.AddTrainCar(traincarActualCollided, lastAnswer);
    }
    else {
        //El vagon de la vía se pierde caboom
        delete traincarActualCollided;
        // Y el tren pierde el ultimo vagon que ya tenia
        train.RemoveLast();
    }

    traincarActualCollided = nullptr; // Limpiamos

    // Chequeo de derrota
    if (train.GetSize() == 0) {
        currentStatus = GameState::GAMEOVER;
    }
    else {
        ecuacion.GenerateAgain();
        currentStatus = GameState::PLAYING;
    }
}

void Game::Draw() {
    BeginDrawing();
    ClearBackground(RAYWHITE);
   
    map.Update();
    train.Draw();
	DrawTexture(texSalida, 0, SPACE_BETWEEN_TRACKS - texSalida.height, WHITE);
	DrawTexture(texLlegada, screenWidth - texLlegada.width, SPACE_BETWEEN_TRACKS * 3 - texLlegada.height, WHITE);
   
    // Dibujar vagones que estan esperando en la via
    for (TrainCar* v : vagonesSueltos) {
        v->Draw();
    }
    //Estados del juego
    if (currentStatus == GameState::WAITING_RTA) {
        hud.DrawEquation(ecuacion.GetAskText(), askTimer.tiempoRestante);
        hud.DrawKeyboard();
    }

    if (currentStatus == GameState::GAMEOVER) {
        DrawRectangle(0, 0, screenWidth, screenHeight, Fade(RED, 0.5f));
        DrawText("GAME OVER", 300, 250, 50, WHITE);
        DrawText("Presiona R para reiniciar", 310, 320, 20, RAYWHITE);
    }

    if (currentStatus == GameState::VICTORI) {
        DrawRectangle(0, 0, screenWidth, screenHeight, Fade(GREEN, 0.5f));
        DrawText("¡VICTORIA!", 300, 250, 50, WHITE);
        DrawText("Presiona R para reiniciar", 310, 320, 20, RAYWHITE);
	}

    //debug
    //DrawText(TextFormat("Vagones sueltos: %d", vagonesSueltos.size()), 10, 10, 20, BLACK);
    
    EndDrawing();
}

Game::~Game() {
    map.~Map();
    UnloadTexture(texLoco);
    UnloadTexture(texVagon);
    CloseWindow();
}