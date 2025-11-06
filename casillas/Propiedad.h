#ifndef PROPIEDAD_H
#define PROPIEDAD_H

#include <string>

struct Propiedad {
    std::string type;
    std::string subType;
    std::string name;
    std::string color;
    int value;
    bool hipotecada;
    int alquiler[6];
};

// OPERACIONES
Propiedad CrearPropiedad(std::string, std::string, std::string, bool, int, int[6]);
#endif