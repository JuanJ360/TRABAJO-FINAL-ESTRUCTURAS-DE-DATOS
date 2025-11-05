#ifndef PROPIEDAD_H
#define PROPIEDAD_H

#include <string>

struct Propiedad {
    std::string type;
    std::string name;
    std::string color;
    int value;
    int alquiler;
    int costoConstruirCasa;
    bool flagCasa;
    int costoConstruirHotel;
    bool flagHotel;
};

// OPERACIONES
Propiedad CrearPropiedad(std::string);
#endif