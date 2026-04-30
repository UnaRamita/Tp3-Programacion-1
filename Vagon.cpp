#include "Vagon.h"

TrainCar::TrainCar(Vector2 pos, Texture2D tex, int val) {
    posicion = pos;
    textura = tex;
    valor = val;                                
}

void TrainCar::Draw() {
    // Dibujamos la textura en la pos
    DrawTextureV(textura, posicion, WHITE);

    // Si el vagón tiene un valor asignado lo dibujamos encima
    if (valor > 0) {
        const char* textoValor = TextFormat("%d", valor);

        // Calculamos el centro para que el numero quede centrado en el vagon
        int fontSize = 20;
        int textWidth = MeasureText(textoValor, fontSize);

        Vector2 posicionTexto = {
            posicion.x + (textura.width / 2) - (textWidth / 2),
            posicion.y + (textura.height / 2) - (fontSize / 2)
        };

        DrawText(textoValor, (int)posicionTexto.x, (int)posicionTexto.y, fontSize, BLACK);
    }
}

TrainCar::~TrainCar(){}