#include "Ecuacion.h"

Ecuacion::Ecuacion() {
    // Inicializamos en 0,luego llamo a GenerarNueva
    n1 = n2 = n3 = 0;
    resultadoCorrecto = 0;
}

void Ecuacion::GenerateAgain() {
    // Uso la funcion de Raylib para obtener numeros altorios
    n1 = GetRandomValue(0, 9);
    n2 = GetRandomValue(0, 9);
    n3 = GetRandomValue(0, 9);

    resultadoCorrecto = n1 + n2 + n3;
}

bool Ecuacion::Check(int respuestaUsuario) {
    return (respuestaUsuario == resultadoCorrecto);
}

const char* Ecuacion::GetAskText() {
    // TextFormat{ para pasarle directamente a DrawText
    return TextFormat("%d + %d + %d = ?", n1, n2, n3);
}                                                               