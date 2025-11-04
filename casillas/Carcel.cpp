#include "Carcel.h"

// implementación de Carcel.h

Carcel CrearCarcel() {
    Carcel carcel;
    return carcel;
}

void Arrestar(Carcel& carcel, User* user) {
    carcel.prisioneros[user->name] = {user, 0};
}

void LiberarDeLaCarcel(Carcel& carcel, std::string name) {
    carcel.prisioneros.erase(name);
}

// se necesita el nombre porque los turnos en esta implementación son individualemente para cada usuario y no para
// toda la partida
void AumentarTurnos(Carcel& carcel, std::string name) {
    carcel.prisioneros[name].second++;
}

bool EstaArrestado(const Carcel& carcel, const std::string& name) {
    return carcel.prisioneros.find(name) != carcel.prisioneros.end();
}