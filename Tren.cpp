#include "Tren.h"
#include "Config.h"

Tren::Tren() {
}

Tren::~Tren() {
    // Limpieza de memoria                                                  
    for (Vagon* v : formacion) {
        delete v;
    }
    formacion.clear();
}

void Tren::Init(Texture2D texLoco, Texture2D texVagon) {
    // Creamos la Locomotora
    // La ponemos en una posición inicial
    Locomotora* loco = new Locomotora({ 100,(float)CARRIL_ALTURA - texLoco.height }, texLoco, TREN_VELOCIDAD);
    formacion.push_back(loco);

    // Agrego los 2 vagones iniciales al fondo
    for (int i = 0; i < 2; i++) {
        int valorRandom = GetRandomValue(0, 99);
        // Calculamos la posición para que queden atrás de la locomotora
        float posX = 100 - ((i + 1)* (texVagon.width));
        Vagon* v = new Vagon({ posX, (float)CARRIL_ALTURA - texVagon.height }, texVagon, valorRandom);
        formacion.push_back(v);
    }
}

void Tren::Actualizar(float dt) {
    // Movemos cada elemento de la lista

    // Movemos la Locomotora (que es la front())
    Vagon* loco = formacion.front();
    static_cast<Locomotora*>(loco)->Actualizar(dt);

    // Iteramos el resto de los vagones
    auto itActual = formacion.begin();
    auto itAnterior = itActual;
    itActual++; // Empezamos desde el primer vagón después de la locomotora

    while (itActual != formacion.end()) {
        Vagon* v = *itActual;
        Vagon* anterior = *itAnterior;

        // Movemos el vagón actual a la misma velocidad
        Vector2 pos = v->GetPosicion();
        pos.x += TREN_VELOCIDAD * dt;

        //salto
        if (pos.x > GetScreenWidth()) {
            pos.x = -v->GetRec().width;
            pos.y += CARRIL_ALTURA;
        }
		//por si se sale por abajo                                                          
        if (pos.y > GetScreenHeight()) {
            pos.y -= CARRIL_ALTURA;
        }
        v->SetPosicion(pos);
        //esta parte es por que se me solpaban cuando bajan de carril
        // Mientras el rectángulo de este vagón choque con el de adelante lo muevo hacia atras
        Rectangle rectActual = v->GetRec();
        Rectangle rectAnterior = anterior->GetRec();

        // veo si se solapan en el mismo carril (misma Y)
        if (rectActual.y == rectAnterior.y) {
            if (CheckCollisionRecs(rectActual, rectAnterior)) {
                // Lo muevo atras
                pos.x = rectAnterior.x - rectActual.width;
                v->SetPosicion(pos);
            }
        }
		//este lo puse por que cuando se pasaba de piso se solapaban con la locomotora
        if (CheckCollisionRecs(rectActual, loco->GetRec()) && rectActual.x != loco->GetRec().x) {
            // Si sigue chocando, lo muevo un poco más atrás (en caso de que el salto haya sido muy grande)
            pos.x -= 1; // Ajuste extra
            v->SetPosicion(pos);
        }

        itAnterior = itActual;
        itActual++;
    }
}

void Tren::AgregarVagon(Vagon* nuevo,int valor) {

    nuevo->setValor(valor);
    // agregamos al final
    float posX = formacion.back()->GetPosicion().x;
    formacion.push_back(nuevo);
	formacion.back()->SetPosicion({ posX - nuevo->GetRec().width, nuevo->GetPosicion().y});

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