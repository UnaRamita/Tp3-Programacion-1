#include "Mapa.h"
#include "Config.h"

Mapa::Mapa() {
    fondo = { 0 };
    via = { 0 };
}

void Mapa::Init(Texture2D texFondo, Texture2D texVia) {
    fondo = texFondo;
    via = texVia;
}

void Mapa::Update() {
    // Dibujamos el fondo estático
    DrawTexture(fondo, 0, 0, WHITE);

    // Dibujamos las vías en cada carril definido en Config.h
    for (int i = 0; i < 3; i++) {
        int yPos = 100 + (i * CARRIL_ALTURA);
        // Dibujamos la vía a lo largo de toda la pantalla (puedes usar un bucle si la textura es chica)
        DrawTexture(via, 0, yPos + 40, WHITE);
    }
}

Mapa::~Mapa() {
    UnloadTexture(fondo);
    UnloadTexture(via);
}