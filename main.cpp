#include "raylib.h"
#include <string>

int main() {
    InitWindow(600, 600, "Template UNL - Tecnicatura en Diseño y Programación de Videojuegos");
    std::string texto = "Tecnicatura en Diseño y Programación de Videojuegos";
    int ancho = MeasureText(texto.c_str(), 20);

    while(!WindowShouldClose()) {
        ClearBackground(WHITE);
        int x = (GetScreenWidth() - ancho) / 2;
        DrawText(texto.c_str(), x, 270, 20, RED);
        EndDrawing();
    }
    
    return 0;
}