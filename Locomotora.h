#pragma once
#include "Vagon.h"

class Locomotora : public TrainCar {
private:
    float velocidad;

public:
    // Paso el valor 0 o un valor especial porque es la locomotora// paso 0 
    Locomotora(Vector2 pos, Texture2D tex, float vel);

    void Update(float dt); // Aca sucede el movimiento basicamente
    void Draw();  //dibujado

    Rectangle GetBounds();
};
