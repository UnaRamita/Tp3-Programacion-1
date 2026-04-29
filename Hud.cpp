#include "Hud.h"
#include "Config.h"

Hud::Hud() {
    inputActual = "";
    // Definimos la grilla del teclado (3 columnas x 4 filas)
    float startX = 300;
    float startY = 400;
    float ancho = 60;
    float alto = 60;

    for (int i = 0; i < 12; i++) {
        botones[i] = { startX + (i % 3) * (ancho + 10), startY + (i / 3) * (alto + 10), ancho, alto };
    }
}

void Hud::DibujarTeclado() {
    for (int i = 0; i < 12; i++) {
        // Si el mouse está encima, lo pintamos de otro color
        Color colorBoton = CheckCollisionPointRec(GetMousePosition(), botones[i]) ? LIGHTGRAY : GRAY;

        DrawRectangleRec(botones[i], colorBoton);
        DrawRectangleLinesEx(botones[i], 2, DARKGRAY);

        // Dibujamos el número/texto centrado en el botón
        DrawText(etiquetas[i], botones[i].x + 20, botones[i].y + 20, 20, BLACK);
    }

    // Dibujamos lo que el usuario va escribiendo
    DrawText(TextFormat("Respuesta: %s", inputActual.c_str()), 300, 350, 30, BLUE);
}

int Hud::ActualizarTeclado() {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePos = GetMousePosition();

        for (int i = 0; i < 12; i++) {
            if (CheckCollisionPointRec(mousePos, botones[i])) {
                if (i < 10) { // Botones 0-9 (ajustar según orden de etiquetas)
                    inputActual += etiquetas[i];
                }
                else if (std::string(etiquetas[i]) == "DEL") {
                    if (!inputActual.empty()) inputActual.pop_back();
                }
                else if (std::string(etiquetas[i]) == "OK") {
                    if (inputActual.empty()) return -1;
                    int finalRes = std::stoi(inputActual);
                    ResetInput();
                    return finalRes;
                }
            }
        }
    }
    return -1; // No se confirmó nada todavía
}