#ifndef CASILLA_H
#define CASILLA_H

#include <string>

struct Casilla {
    std::string tipo;
    int indiceTipo;
};

Casilla CrearCasilla(std::string, int);

#endif