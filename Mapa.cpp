#include "Mapa.h"
#include "Config.h"

Map::Map() {
    fondo = { 0 };
    via = { 0 };
}

void Map::Init(Texture2D texFondo, Texture2D texVia) {
    fondo = texFondo;
    via = texVia;
}

void Map::Update() {
    // Dibujo el fondo estatico
    DrawTexture(fondo, 0, 0, WHITE);

    // Dibujo las vias en cada carril definido en Config.h
    for (int i = 0; i < 3; i++) {
        int yPos = 100 + (i * SPACE_BETWEEN_TRACKS);
        // Dibujo la via a lo largo de toda la pantalla
        DrawTexture(via, 0, yPos + 40, WHITE);
    }
}

Map::~Map() {
    UnloadTexture(fondo);
    UnloadTexture(via);
}