#pragma once
#include "raylib.h"
#include <string>

class Hud {
private:
    std::string inputActual; // Lo que el usuario va tipeando
    Rectangle botones[12];   // 0-9, Borrar y Enter
    const char* etiquetas[12] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "DEL", "OK" };

public:
    Hud();
    void DibujarTeclado();
    void DibujarEcuacion(const char* pregunta, float tiempo);

    // Retorna -1 si no se tocó nada, o el valor final si tocó OK
    int ActualizarTeclado();

    void ResetInput() { inputActual = ""; }
    std::string GetInput() { return inputActual; }
};