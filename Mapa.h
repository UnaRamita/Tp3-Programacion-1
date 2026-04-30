#pragma once
#include "raylib.h"

class Mapa {
private:
    Texture2D fondo;
    Texture2D via;

public:
    Mapa();
    void Init(Texture2D texFondo, Texture2D texVia);
    void Update();
    ~Mapa();
};