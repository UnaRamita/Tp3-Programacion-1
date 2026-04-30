#pragma once  
#include "raylib.h"
#include <vector>
#include "Vagon.h"
#include "Tren.h"
#include "Ecuacion.h"
#include "Hud.h"
#include "Timer.h"
#include "Mapa.h"
#include "GameStates.h"

class Game {
private:
    int ultimaRespuesta;

    GameState estadoActual;
    Tren tren;
    Ecuacion ecuacion;
    Hud hud;
    Timer timerPregunta;
    Mapa mapa;
	Rectangle rectLlegada;

    std::vector<Vagon*> vagonesSueltos;
    Vagon* vagonActualColisionado;

    // Texturas globales
    Texture2D texLoco, texVagon, texFondo, texVia, texSalida, texLlegada;

    void VerificarColisiones();
    void ProcesarRespuesta(int rta);
    void Draw();

public:
    Game();
    ~Game();
    void Inits();
    void Run();
};
