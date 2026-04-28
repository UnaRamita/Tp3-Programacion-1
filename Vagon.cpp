#include "Vagon.h"

// Constructor: Inicializa la posición, la textura y el valor numérico del vagón
Vagon::Vagon(Vector2 pos, Texture2D tex, int val) {
    posicion = pos;
    textura = tex;
    valor = val;                                
}

// Dibuja el vagón en su posición actual
void Vagon::Dibujar() {
    // Dibujamos la textura en la posición almacenada
    DrawTextureV(textura, posicion, WHITE);

    // Si el vagón tiene un valor asignado (y no es la locomotora), lo dibujamos encima
    // Usamos el valor convertido a texto para Raylib
    if (valor >= 0) {
        const char* textoValor = TextFormat("%d", valor);

        // Calculamos el centro para que el número quede centrado en el vagón
        int fontSize = 20;
        int textWidth = MeasureText(textoValor, fontSize);

        Vector2 posicionTexto = {
            posicion.x + (textura.width / 2) - (textWidth / 2),
            posicion.y + (textura.height / 2) - (fontSize / 2)
        };

        DrawText(textoValor, (int)posicionTexto.x, (int)posicionTexto.y, fontSize, BLACK);
    }
}

// Retorna el rectángulo de colisión del vagón
Rectangle Vagon::GetBounds() {
    return { posicion.x, posicion.y, (float)textura.width, (float)textura.height };
}