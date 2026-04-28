#pragma once
#include "raylib.h"

class Mapa {
private:
    Texture2D fondo;
    Texture2D piso;
    Texture2D via;

public:
    Mapa();
    void Inicializar(Texture2D texFondo, Texture2D texPiso, Texture2D texVia);
    void Dibujar();
    void Descargar();
};