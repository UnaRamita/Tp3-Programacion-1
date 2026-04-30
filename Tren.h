#pragma once
#include <list>
#include "Vagon.h"
#include "Locomotora.h"

class Tren {
private:
    // La joya de la corona: la lista de la STL
    std::list<Vagon*> formacion;

public:
    Tren();
    ~Tren(); // Para liberar los punteros

    // Setup inicial (Locomotora + 2 vagones)
    void Init(Texture2D texLoco, Texture2D texVagon);

    // Bucle principal
    void Actualizar(float dt);
    void Dibujar();

    // Métodos de la formación
    void AgregarVagon(Vagon* nuevo,int valor);
    void ExplotarUltimo();

    // Getters útiles para el Game.cpp
    int GetCantidad();
    Vector2 GetPosicionCabeza();
};
