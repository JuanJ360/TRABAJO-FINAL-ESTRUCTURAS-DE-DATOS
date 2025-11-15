#ifndef PROPIEDAD_H
#define PROPIEDAD_H

#include <string>
#include <vector>

struct Propiedad {
    std::string tipo;
    std::string subTipo;
    std::string name;
    std::string color;
    int valor;
    bool hipotecada;
    int alquiler[6];
};

// OPERACIONES
Propiedad CrearPropiedad(std::string, std::string, std::string, bool, int, int[6]);

#endif