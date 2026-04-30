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
    int lastAnswer;

    GameState currentStatus;
    Train train;
    Ecuacion ecuacion;
    Hud hud;
    Timer askTimer;
    Map map;
	Rectangle rectLlegada;

    std::vector<TrainCar*> vagonesSueltos;
    TrainCar* traincarActualCollided;

    // Texturas globales
    Texture2D texLoco, texVagon, texFondo, texVia, texSalida, texLlegada;

    void CheckCollider();
    void CheckAnswer(int rta);
    void Draw();

public:
    Game();
    ~Game();
    void Inits();
    void Run();
};
