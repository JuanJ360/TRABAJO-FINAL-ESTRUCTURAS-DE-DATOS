#ifndef FERROCARRIL_H
#define FERROCARRIL_H

#include <string>

struct Ferrocarril {
    std::string tipo;
    std::string name;
    int value;
    bool hipotecada;
    int alquiler[6];
};

// OPERACIONES
Ferrocarril CrearFerrocarril(std::string);

#endif