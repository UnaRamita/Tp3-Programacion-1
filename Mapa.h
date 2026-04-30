#pragma once
#include "raylib.h"

class Map {
private:
    Texture2D fondo;
    Texture2D via;

public:
    Map();
    void Init(Texture2D texFondo, Texture2D texVia);
    void Update();
    ~Map();
};