#include "Hud.h"
#include "Config.h"

Hud::Hud() {
    inputActual = "";
    // Definimos la grilla del teclado (3 columnas x 4 filas)
    float startX = 300;
    float startY = 200;
    float ancho = 60;
    float alto = 60;

    for (int i = 0; i < 12; i++) {
        botones[i] = { startX + (i % 3) * (ancho + 10), startY + (i / 3) * (alto + 10), ancho, alto };
    }
}

void Hud::DrawKeyboard() {
    for (int i = 0; i < 12; i++) {
        // Si el mouse esta encima, lo pintamos de otro color
        Color colorBoton = CheckCollisionPointRec(GetMousePosition(), botones[i]) ? LIGHTGRAY : GRAY;

        DrawRectangleRec(botones[i], colorBoton);
        DrawRectangleLinesEx(botones[i], 2, DARKGRAY);

        // Dibujo el numero/texto centrado en el boton
        DrawText(etiquetas[i], botones[i].x + 20, botones[i].y + 20, 20, BLACK);
    }

    // Dibujo lo que el player va escribiendo
    DrawText(TextFormat("Respuesta: %s", inputActual.c_str()), 300, 500, 30, BLUE);
}

int Hud::ActualizarTeclado(float tiempo) {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePos = GetMousePosition();

        for (int i = 0; i < 12; i++) {
            if (CheckCollisionPointRec(mousePos, botones[i])) {
                if (i < 10) { // Botones 0-9
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
   if (tiempo <= 0) {
        return 9999; // por poner un numero que seguro es erroneo 
   }
    return -1; // No se confirmó nada todavía
}
void Hud::DrawEquation(const char* pregunta, float tiempo) {
    // Dibujo un recuadro para la ecuacion
    DrawRectangle(200, 50, 400, 100, Fade(LIGHTGRAY, 0.8f));
    DrawRectangleLines(200, 50, 400, 100, DARKGRAY);

    // Dibujo el texto de la ecuacion
    DrawText(pregunta, 250, 80, 40, BLACK);

    // Dibujo el tiempo restante 
    Color colorTiempo = (tiempo < 2.0f) ? RED : DARKGREEN;
    DrawText(TextFormat("Tiempo: %.0f", tiempo), 250, 160, 20, colorTiempo);
}
