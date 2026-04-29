#pragma once
#include "Vagon.h"

class Locomotora : public Vagon {
private:
    float velocidad;

public:
    // Pasamos el valor 0 o un valor especial porque es la locomotora
    Locomotora(Vector2 pos, Texture2D tex, float vel);

    void Actualizar(float dt); // Aquí sucede la magia del movimiento
    void Dibujar();   // Por si querés que la locomotora brille o sea distinta
};
