#pragma once
#include "raylib.h"
#include <string>

class Ecuacion {
private:
    int n1, n2, n3;
    int resultadoCorrecto;

public:
    Ecuacion();

    // Genera 3 numeros nuevos entre 0 y 9 y calcula el resultado
    void GenerateAgain();

    // Compara la respuesta del usuario con el resultado real
    bool Check(int respuestaUsuario);

    // Getters para mostrar en el HUD
    int GetN1() const { return n1; }
    int GetN2() const { return n2; }
    int GetN3() const { return n3; }
    int GetRes() const { return resultadoCorrecto; }

    // Devuelve la cadena "N1 + N2 + N3 = ?" para dibujar
    const char* GetAskText();
};