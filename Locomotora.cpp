#include "Locomotora.h"
#include "Config.h" // Para usar SCREEN_WIDTH y CARRIL_ALTURA                                                                                                   

Locomotora::Locomotora(Vector2 pos, Texture2D tex, float vel)
    : Vagon(pos, tex, 0), velocidad(vel) {
    // El 0 es porque la locomotora no tiene numero de ecuación
}

void Locomotora::Actualizar(float dt) {
    // Movimiento constante a la derecha
    posicion.x += velocidad * dt;

    // Lógica de "Wrap" (Cambio de carril)
    if (posicion.x > GetScreenWidth()) {
        posicion.x = -textura.width;      // Reaparece por la izquierda
        posicion.y += CARRIL_ALTURA;      // Baja al siguiente carril

        // Opcional: Si llega al fondo de la pantalla
        if (posicion.y > GetScreenHeight()) {
            posicion.y -= CARRIL_ALTURA;
        }
    }
}

// Retorna el rectángulo de colisión del vagón
Rectangle Locomotora::GetBounds() {
    return { posicion.x, posicion.y, (float)textura.width, (float)textura.height };
}

void Locomotora::Dibujar() {
    // Dibujamos la textura (podés rotarla o tintarla si está dañada)
    DrawTextureV(textura, posicion, WHITE);
}