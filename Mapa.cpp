#include "Mapa.h"
#include "Config.h"

Mapa::Mapa() {}

void Mapa::Inicializar(Texture2D texFondo, Texture2D texPiso, Texture2D texVia) {
    fondo = texFondo;
    piso = texPiso;
    via = texVia;
}

void Mapa::Dibujar() {
    // Dibujamos el fondo estático
    DrawTexture(fondo, 0, 0, WHITE);

    // Dibujamos las vías en cada carril definido en Config.h
    for (int i = 0; i < 4; i++) {
        int yPos = 100 + (i * CARRIL_ALTURA);
        // Dibujamos la vía a lo largo de toda la pantalla (puedes usar un bucle si la textura es chica)
        DrawTexture(via, 0, yPos + 40, WHITE);
    }
}

void Mapa::Descargar() {
    UnloadTexture(fondo);
    UnloadTexture(piso);
    UnloadTexture(via);
}