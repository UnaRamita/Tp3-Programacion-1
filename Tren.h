#pragma once
#include <list>
#include "Vagon.h"
#include "Locomotora.h"

class Train {
private:
    //la lista de la STL
    std::list<TrainCar*> formacion;

public:
    Train();
    ~Train();

    // Setup inicial (Locomotora + 2 vagones)
    void Init(Texture2D texLoco, Texture2D texVagon);

    // Bucle principal
    void Update(float dt);
    void Draw();

    // Metodos de la formacion
    void AddTrainCar(TrainCar* nuevo,int valor);
    void RemoveLast();

    // Getters que me son utiles para el Game.cpp
    int GetSize();
    Vector2 GetPHeadPos();
};
