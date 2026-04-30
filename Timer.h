#pragma once
#include "raylib.h"

struct Timer {
    float tiempoRestante;
    bool activo;

    // Inicia el contador con un tiempo dado
    void Start(float segundos) {
        tiempoRestante = segundos;
        activo = true;
    }

    // Actualiza el tiempo restando el frame time
    void Update() {
        if (activo) {
            tiempoRestante -= GetFrameTime();
            if (tiempoRestante <= 0) {
                tiempoRestante = 0;
                activo = false;
            }
        }
    }

    // Verifica si se termino el tiempo
    bool TimeIsUp() const {
        if (activo && tiempoRestante <= 0) {
            return true;
		}
		else { return false; }
    }
};
                                    