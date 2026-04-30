#include "Locomotora.h"
#include "Config.h"                                                                                               

Locomotora::Locomotora(Vector2 pos, Texture2D tex, float vel)
    : TrainCar(pos, tex, 0), velocidad(vel) {
    // El 0 es porque la locomotora no tiene numero de ecuacion
}

void Locomotora::Update(float dt) {
    // Movimiento constante a la derecha
    posicion.x += velocidad * dt;

    // "Wrap" (Cambio de carril)
    if (posicion.x > GetScreenWidth()) {
        posicion.x = -textura.width;      // Reaparece por la izquierda
        posicion.y += SPACE_BETWEEN_TRACKS;      // Baja al siguiente carril

        //Si llega al fondo de la pantalla //no deberia pasar al final del proyecto igual
        if (posicion.y > GetScreenHeight()) {
            posicion.y -= SPACE_BETWEEN_TRACKS;
        }
    }
}

// rectangulo de colisión del vagón
Rectangle Locomotora::GetBounds() {
    return { posicion.x, posicion.y, (float)textura.width, (float)textura.height };
}

void Locomotora::Draw() {
    // Dibujo la textura
    DrawTextureV(textura, posicion, WHITE);
}