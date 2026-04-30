#pragma once
#include "raylib.h"

class Vagon {
protected:
    Vector2 posicion;
    Texture2D textura;
    int valor;

public:
    Vagon(Vector2 pos, Texture2D tex, int val);
    ~Vagon();

    void Dibujar();

    // Getters y Setters
    Vector2 GetPosicion() { return posicion; }
    void SetPosicion(Vector2 pos) { posicion = pos; }
	void setValor(int val) { valor = val; }
    int GetValor() { return valor; }
    // Devuelve ancho(x) y alto(y) correctamente
    Rectangle GetRec() { return {posicion.x,posicion.y, (float)textura.width, (float)textura.height }; }
};