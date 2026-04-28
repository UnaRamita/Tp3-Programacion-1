#include "Game.h"
#include "Config.h"

Game::Game() {
    estadoActual = GameState::MENU;
}

void Game::Init() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Tren Radioactivo - UNL");
    SetTargetFPS(60);

    // Carga de texturas (asegurate de tener los archivos en la carpeta assets)
    texLoco = LoadTexture("assets/locomotora.png");
    texVagon = LoadTexture("assets/vagon.png");
    texFondo = LoadTexture("assets/fondo.png");
    texVia = LoadTexture("assets/via.png");

    mapa.Inicializar(texFondo, texFondo, texVia);
    tren.Inicializar(texLoco, texVagon);
    ecuacion.GenerarNueva();
}

void Game::Update() {
    float dt = GetFrameTime();

    switch (estadoActual) {
    case GameState::MENU:
        if (IsKeyPressed(KEY_ENTER)) estadoActual = GameState::JUGANDO;
        break;

    case GameState::JUGANDO:
        tren.Actualizar(dt);
        // Simulación: si presionas espacio, aparece una pregunta (luego será por colisión)
        if (IsKeyPressed(KEY_SPACE)) {
            estadoActual = GameState::ESPERANDO_RTA;
            timerPregunta.Iniciar(TIEMPO_LIMITE_PREGUNTA);
            hud.ResetInput();
        }
        break;

    case GameState::ESPERANDO_RTA:
        timerPregunta.Actualizar();

        // Obtenemos la respuesta del teclado numérico del HUD
        int respuesta = hud.ActualizarTeclado();

        if (respuesta != -1) {
            ProcesarRespuesta(respuesta);
        }

        if (timerPregunta.Termino()) {
            // Si se acaba el tiempo, pierde un vagón
            tren.ExplotarUltimo();
            ecuacion.GenerarNueva();
            estadoActual = GameState::JUGANDO;
        }
        break;

    case GameState::GAMEOVER:
        if (IsKeyPressed(KEY_R)) Init(); // Reiniciar
        break;
    }
}

void Game::ProcesarRespuesta(int rta) {
    if (ecuacion.Verificar(rta)) {
        // Correcto: Agregamos vagón nuevo
        Vagon* nuevo = new Vagon({ -100, 0 }, texVagon, rta);
        tren.AgregarVagon(nuevo);
    }
    else {
        // Incorrecto: Explota el último
        tren.ExplotarUltimo();
    }

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

    mapa.Dibujar();
    tren.Dibujar();

    if (estadoActual == GameState::ESPERANDO_RTA) {
        hud.DibujarEcuacion(ecuacion.GetTextoPregunta(), timerPregunta.tiempoRestante);
        hud.DibujarTeclado();
    }

    if (estadoActual == GameState::MENU) {
        DrawText("TREN RADIOACTIVO", 200, 200, 40, DARKBLUE);
        DrawText("Presiona ENTER para comenzar", 220, 300, 20, GRAY);
    }

    if (estadoActual == GameState::GAMEOVER) {
        DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Fade(RED, 0.5f));
        DrawText("GAME OVER", 300, 250, 50, WHITE);
        DrawText("Presiona R para reiniciar", 310, 320, 20, RAYWHITE);
    }

    EndDrawing();
}

void Game::Unload() {
    mapa.Descargar();
    UnloadTexture(texLoco);
    UnloadTexture(texVagon);
    CloseWindow();
}

bool Game::DeberiaCerrar() {
    return WindowShouldClose();
}