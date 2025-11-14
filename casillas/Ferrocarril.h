#ifndef FERROCARRIL_H
#define FERROCARRIL_H

#include <string>

struct Ferrocarril {
    std::string tipo;
    std::string name;
};

// OPERACIONES
Ferrocarril CrearFerrocarril(std::string);

#endif