#include "Carcel.h"

// implementación de Carcel.h

Carcel CrearCarcel() {
    Carcel carcel;
    return carcel;
}

void Arrestar(Carcel& carcel, User* user) {
    carcel.prisioneros[user->nombre] = {user, 0};
}

void LiberarDeLaCarcel(Carcel& carcel, std::string nombre) {
    carcel.prisioneros.erase(nombre);
}

// se necesita el nombre porque los turnos en esta implementación son individualemente para cada usuario y no para
// toda la partida
void AumentarTurnos(Carcel& carcel, std::string nombre) {
    carcel.prisioneros[nombre].second++;
}

bool EstaArrestado(const Carcel& carcel, const std::string& nombre) {
    return carcel.prisioneros.find(nombre) != carcel.prisioneros.end();
}