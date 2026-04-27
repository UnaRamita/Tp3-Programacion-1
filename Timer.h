#pragma once
#include "raylib.h"

struct Timer {
    float tiempoRestante;
    bool activo;

    // Inicia el contador con un tiempo dado
    void Iniciar(float segundos) {
        tiempoRestante = segundos;
        activo = true;
    }

    // Actualiza el tiempo restando el frame time
    void Actualizar() {
        if (activo) {
            tiempoRestante -= GetFrameTime();
            if (tiempoRestante <= 0) {
                tiempoRestante = 0;
                activo = false;
            }
        }
    }

    // Verifica si se terminó el tiempo
    bool Termino() const {
        return (activo && tiempoRestante <= 0);
    }
};
