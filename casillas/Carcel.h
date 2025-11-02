#ifndef CARCEL_H
#define CARCEL_H

#include <utility>
#include <map>
#include "./User.h"

struct Carcel {
    std::map<std::string, std::pair<User*, int>> usuarios; // userName : <User, turnos en la carcel>
};

Carcel CrearCarcel();
void Arrestar(Carcel&, User*);
void LiberarDeLaCarcel(Carcel&, std::string);
bool EstaArrestado(const Carcel&, std::string);
void ReglaTercerTurno(Carcel&, std::string);

#endif