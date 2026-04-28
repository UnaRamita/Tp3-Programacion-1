#include "Ecuacion.h"

Ecuacion::Ecuacion() {
    // Inicializamos en 0 por seguridad, aunque luego llamaremos a GenerarNueva
    n1 = n2 = n3 = 0;
    resultadoCorrecto = 0;
}

void Ecuacion::GenerarNueva() {
    // Usamos la función de Raylib para obtener números aleatorios
    n1 = GetRandomValue(0, 9);
    n2 = GetRandomValue(0, 9);
    n3 = GetRandomValue(0, 9);

    resultadoCorrecto = n1 + n2 + n3;
}

bool Ecuacion::Verificar(int respuestaUsuario) {
    return (respuestaUsuario == resultadoCorrecto);
}

const char* Ecuacion::GetTextoPregunta() {
    // TextFormat es una función de Raylib muy útil que devuelve un const char* // formateado, ideal para pasarle directamente a DrawText
    return TextFormat("%d + %d + %d = ?", n1, n2, n3);
}                                                               