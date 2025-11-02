#ifndef FERROCARRIL_H
#define FERROCARRIL_H

#include <string>

struct Ferrocarril {
    std::string type;
    std::string name;
};

// OPERACIONES
Ferrocarril CrearFerrocarril(std::string);

#endif