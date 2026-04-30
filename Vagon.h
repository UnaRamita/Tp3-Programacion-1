#pragma once
#include "raylib.h"

class TrainCar {
protected:
    Vector2 posicion;
    Texture2D textura;
    int valor;

public:
    TrainCar(Vector2 pos, Texture2D tex, int val);
    ~TrainCar();

    void Draw();

    // Getters y Setters
    Vector2 GetPos() { return posicion; }
    void SetPos(Vector2 pos) { posicion = pos; }
	void setVal(int val) { valor = val; }
    int GetVal() { return valor; }
	// Devuelve el rectangulo de colision del vagon
    Rectangle GetRec() { return {posicion.x,posicion.y, (float)textura.width, (float)textura.height }; }
};