#pragma once
#include "raylib.h"
#include "Tren.h"
#include "Ecuacion.h"
#include "Hud.h"
#include "Timer.h"
#include "Mapa.h"
#include "GameStates.h"

class Game {
private:
    GameState estadoActual;
    Tren tren;
    Ecuacion ecuacion;
    Hud hud;
    Timer timerPregunta;
    Mapa mapa;

    // Texturas globales
    Texture2D texLoco, texVagon, texFondo, texVia;

    void VerificarColisiones();
    void ProcesarRespuesta(int rta);

public:
    Game();
    void Init();
    void Update();
    void Draw();
    void Unload();
    bool DeberiaCerrar();
};
