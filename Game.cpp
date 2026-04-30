#include "Game.h"
#include "Config.h"

Game::Game() {
    estadoActual = GameState::JUGANDO;

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

    // Carga de texturas (asegurate de tener los archivos en la carpeta assets)
    texLoco = LoadTexture("assets/locomotora.png");
    texVagon = LoadTexture("assets/vagon.png");
    texFondo = LoadTexture("assets/fondo.png");
    texVia = LoadTexture("assets/via.png");
	texSalida = LoadTexture("assets/salida.png");
	texLlegada = LoadTexture("assets/llegada.png");

	rectLlegada = { (float)screenWidth - texLlegada.width, (float)CARRIL_ALTURA * 3 - texLlegada.height, (float)texLlegada.width, (float)texLlegada.height };

    mapa.Init(texFondo, texVia);
    tren.Init(texLoco, texVagon);

    for (int carril = 0; carril < 4; carril++) {
        float yPos = CARRIL_ALTURA * carril - texVagon.height;

        for (int i = 0; i < 2; i++) {
            // Posición X aleatoria entre 200 y el ancho de pantalla - 100
            float xPos = (float)GetRandomValue(200, screenWidth - 100);
            Vagon* nuevoSuelto = new Vagon({ xPos, yPos }, texVagon, 0);
            vagonesSueltos.push_back(nuevoSuelto);
        }
    }

    ecuacion.GenerarNueva();
}
void Game::VerificarColisiones() {
	Rectangle rectLoco = { tren.GetPosicionCabeza().x, tren.GetPosicionCabeza().y, (float)texLoco.width, (float)texLoco.height };
    float yLlegada = (CARRIL_ALTURA * 3) - (texLlegada.height);
    Rectangle rectLlegada = { (float)screenWidth - texLlegada.width, yLlegada, (float)texLlegada.width, (float)texLlegada.height };

    DrawRectangleLines(rectLlegada.x, rectLlegada.y, rectLlegada.width, rectLlegada.height, RED);
	
    // Usamos un iterador para poder borrar el vagon del vector si chocamos
    for (auto it = vagonesSueltos.begin(); it != vagonesSueltos.end(); ++it) {
        if (CheckCollisionRecs(rectLoco, (*it)->GetRec())) {
            if (estadoActual == GameState::JUGANDO) {
                vagonActualColisionado = *it; // Guardamos la referencia

                // Quitamos el vagón de la lista de "sueltos" para que no se dibuje más en la vía
                vagonesSueltos.erase(it);

                // Disparamos la ecuación
                estadoActual = GameState::ESPERANDO_RTA;
                timerPregunta.Iniciar(TIEMPO_LIMITE_PREGUNTA);
                hud.ResetInput();
                break; // Salimos del bucle porque ya chocamos con uno
            }
        }
    }

    if (CheckCollisionRecs(rectLoco, rectLlegada)) {
        if (vagonesSueltos.empty()) { // Solo gana si no quedan vagones en el mapa
            estadoActual = GameState::VICTORIA;
        }
    }
}

void Game::Run() {
    Draw();
    float dt = GetFrameTime();
    switch (estadoActual) {
    case GameState::JUGANDO: 
        tren.Actualizar(dt);
        mapa.Update();
        VerificarColisiones();
        break;

    case GameState::ESPERANDO_RTA:
    {
        timerPregunta.Actualizar();
        mapa.Update();
        // Obtenemos la respuesta del teclado numérico del HUD
        int respuesta = hud.ActualizarTeclado(timerPregunta.tiempoRestante);

        if (respuesta != -1) {
            ultimaRespuesta = respuesta;
            ProcesarRespuesta(respuesta);
        }

        if (timerPregunta.Termino()) {
            // Si se acaba el tiempo, pierde un vagón
            tren.ExplotarUltimo();
            ecuacion.GenerarNueva();
            estadoActual = GameState::JUGANDO;
        }
    }
        break;

    case GameState::GAMEOVER: 
        if (IsKeyPressed(KEY_R)){ 
            Inits(); 
			estadoActual = GameState::JUGANDO;
        } // Reiniciar
   
        break;
	case GameState::VICTORIA:
        if (IsKeyPressed(KEY_R)) {
            Inits();
            estadoActual = GameState::JUGANDO;
        } // Reiniciar
    }


    
}

void Game::ProcesarRespuesta(int rta) {
    if (ecuacion.Verificar(rta)) {
        // CORRECTO: El vagón con el que chocamos se une al tren
        // No creamos uno nuevo, usamos el que ya existía en la vía
        tren.AgregarVagon(vagonActualColisionado, ultimaRespuesta);
    }
    else {
        // INCORRECTO: El vagón de la vía se pierde (borramos memoria)
        delete vagonActualColisionado;
        // Y el tren pierde el último vagón que ya tenía
        tren.ExplotarUltimo();
    }

    vagonActualColisionado = nullptr; // Limpiamos el puntero

    // Chequeo de derrota
    if (tren.GetCantidad() == 0) {
        estadoActual = GameState::GAMEOVER;
    }
    else {
        ecuacion.GenerarNueva();
        estadoActual = GameState::JUGANDO;
    }
}

void Game::Draw() {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    mapa.Update();
    tren.Dibujar();
	DrawTexture(texSalida, 0, CARRIL_ALTURA - texSalida.height, WHITE);
	DrawTexture(texLlegada, screenWidth - texLlegada.width, CARRIL_ALTURA * 3 - texLlegada.height, WHITE);
   
    // Dibujar vagones que están esperando en la vía
    for (Vagon* v : vagonesSueltos) {
        v->Dibujar();
    }
    //Estados del juego
    if (estadoActual == GameState::ESPERANDO_RTA) {
        hud.DibujarEcuacion(ecuacion.GetTextoPregunta(), timerPregunta.tiempoRestante);
        hud.DibujarTeclado();
    }

    if (estadoActual == GameState::GAMEOVER) {
        DrawRectangle(0, 0, screenWidth, screenHeight, Fade(RED, 0.5f));
        DrawText("GAME OVER", 300, 250, 50, WHITE);
        DrawText("Presiona R para reiniciar", 310, 320, 20, RAYWHITE);
    }

    if (estadoActual == GameState::VICTORIA) {
        DrawRectangle(0, 0, screenWidth, screenHeight, Fade(GREEN, 0.5f));
        DrawText("¡VICTORIA!", 300, 250, 50, WHITE);
        DrawText("Presiona R para reiniciar", 310, 320, 20, RAYWHITE);
	}

    EndDrawing();
}

Game::~Game() {
    mapa.~Mapa();
    UnloadTexture(texLoco);
    UnloadTexture(texVagon);
    CloseWindow();
}