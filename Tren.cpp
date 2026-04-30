#include "Tren.h"
#include "Config.h"

Train::Train() {
}

Train::~Train() {                                               
    for (TrainCar* v : formacion) {
        delete v;
    }
    formacion.clear();
}

void Train::Init(Texture2D texLoco, Texture2D texVagon) {
    // Cro la Locomotora
    // La ponemos en una posicion inicial
    Locomotora* loco = new Locomotora({ 100,(float)SPACE_BETWEEN_TRACKS - texLoco.height }, texLoco, TRAIN_VEL);
    formacion.push_back(loco);

    // Agrego los 2 vagones iniciales al fondo
    for (int i = 0; i < 2; i++) {
        int valorRandom = GetRandomValue(0, 99);
        // Calculamos la posicion para que queden atras de la locomotora
        float posX = 100 - ((i + 1)* (texVagon.width));
        TrainCar* v = new TrainCar({ posX, (float)SPACE_BETWEEN_TRACKS - texVagon.height }, texVagon, valorRandom);
        formacion.push_back(v);
    }
}

void Train::Update(float dt) {
    // Movemos la Locomotora (que es la del front())
    TrainCar* loco = formacion.front();
    static_cast<Locomotora*>(loco)->Update(dt);

    // Iteramos el resto de los vagones
    auto itActual = formacion.begin();
    auto itAnterior = itActual;
    itActual++;

    while (itActual != formacion.end()) {
        TrainCar* v = *itActual;
        TrainCar* anterior = *itAnterior;

        // Movemos el vagon actual a la misma velocidad
        Vector2 pos = v->GetPos();
        pos.x += TRAIN_VEL * dt;

        //salto
        if (pos.x > GetScreenWidth()) {
            pos.x = -v->GetRec().width;
            pos.y += SPACE_BETWEEN_TRACKS;
        }
		//por si se sale por abajo                                                          
        if (pos.y > GetScreenHeight()) {
            pos.y -= SPACE_BETWEEN_TRACKS;
        }
        v->SetPos(pos);
        //esta parte es por que se me solpaban cuando bajan de carril
        // Mientras el rectangulo de este vagon choque con el de adelante lo muevo hacia atras
        Rectangle rectActual = v->GetRec();
        Rectangle rectAnterior = anterior->GetRec();

        // veo si se solapan en el mismo carril (misma Y)
        if (rectActual.y == rectAnterior.y) {
            if (CheckCollisionRecs(rectActual, rectAnterior)) {
                // Lo muevo atras
                pos.x = rectAnterior.x - rectActual.width;
                v->SetPos(pos);
            }
        }
		//este lo puse por que cuando se pasaba de piso se solapaban con la locomotora igualmente
        if (CheckCollisionRecs(rectActual, loco->GetRec()) && rectActual.x != loco->GetRec().x) {
         
            pos.x -= 1; // Ajuste
            v->SetPos(pos);
        }

        itAnterior = itActual;
        itActual++;
    }
}

void Train::AddTrainCar(TrainCar* nuevo,int valor) {

    nuevo->setVal(valor);
    // agregamos al final
    float posX = formacion.back()->GetPos().x;
    formacion.push_back(nuevo);
	formacion.back()->SetPos({ posX - nuevo->GetRec().width, nuevo->GetPos().y});

}

void Train::RemoveLast() {
    // Si hay algo para borrar
    if (!formacion.empty()) {
        delete formacion.back(); // Borramos el objeto
        formacion.pop_back();    // Lo sacamos de la lista
    }
}

void Train::Draw() {
    // Recorremos la lista y dibujamos cada parte
    for (TrainCar* v : formacion) {
        v->Draw();
    }
}

int Train::GetSize() {
    return (int)formacion.size();
}

Vector2 Train::GetPHeadPos() {
    if (!formacion.empty()) {
        return formacion.front()->GetPos();
    }
    return { 0, 0 };
}