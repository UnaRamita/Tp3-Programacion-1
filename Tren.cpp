#include "Tren.h"
#include "Config.h"

Tren::Tren() {
    // Lista vacía al empezar
}

Tren::~Tren() {
    // Limpieza de memoria (como en tus ejercicios de la facu)
    for (Vagon* v : formacion) {
        delete v;
    }
    formacion.clear();
}

void Tren::Inicializar(Texture2D texLoco, Texture2D texVagon) {
    // 1. Creamos la Locomotora
    // La ponemos en una posición inicial (ej: carril 1)
    Locomotora* loco = new Locomotora({ 100, 100 }, texLoco, TREN_VELOCIDAD);
    formacion.push_back(loco);

    // 2. Agregamos los 2 vagones iniciales al fondo
    for (int i = 0; i < 2; i++) {
        int valorRandom = GetRandomValue(0, 9);
        // Calculamos la posición para que queden atrás de la locomotora
        float posX = 100 - ((i + 1) * (texVagon.width + 10));
        Vagon* v = new Vagon({ posX, 100 }, texVagon, valorRandom);
        formacion.push_back(v);
    }
}

void Tren::Actualizar(float dt) {
    if (formacion.empty()) return;

    // Movemos cada elemento de la lista
    for (Vagon* v : formacion) {
        // Si es el primero (Locomotora), usa su lógica de wrap y velocidad
        if (v == formacion.front()) {
            static_cast<Locomotora*>(v)->Actualizar(dt);
        }
        else {
            // Los vagones siguen a la misma velocidad constante
            Vector2 pos = v->GetPosicion();
            pos.x += TREN_VELOCIDAD * dt;

            // Lógica de wrap (reaparecer y bajar de carril)
            if (pos.x > GetScreenWidth()) {
                pos.x = -v->GetBounds().width;
                pos.y += CARRIL_ALTURA;

                // Si se sale de la pantalla por abajo, vuelve al primer carril
                if (pos.y > GetScreenHeight() - 100) pos.y = 100;
            }
            v->SetPosicion(pos);
        }
    }
}

void Tren::AgregarVagon(Vagon* nuevo) {
    // Simplemente al final, sin vueltas
    formacion.push_back(nuevo);
}

void Tren::ExplotarUltimo() {
    // Si hay algo para borrar (mínimo la locomotora)
    if (!formacion.empty()) {
        delete formacion.back(); // Borramos el objeto de la memoria
        formacion.pop_back();    // Lo sacamos de la lista
    }
}

void Tren::Dibujar() {
    // Recorremos la lista y dibujamos cada parte
    for (Vagon* v : formacion) {
        v->Dibujar();
    }
}

int Tren::GetCantidad() {
    return (int)formacion.size();
}

Vector2 Tren::GetPosicionCabeza() {
    if (!formacion.empty()) {
        return formacion.front()->GetPosicion();
    }
    return { 0, 0 };
}