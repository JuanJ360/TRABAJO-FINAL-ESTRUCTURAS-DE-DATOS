#ifndef PROPIEDAD_H
#define PROPIEDAD_H

#include <string>

struct Propiedad {
    std::string type;
    std::string name;
    std::string color;
    int value;
};

// OPERACIONES
Propiedad CrearPropiedad(std::string);

#endif