#ifndef FERROCARRIL_H
#define FERROCARRIL_H

#include <string>

struct Ferrocarril {
    std::string tipo;
    std::string nombre;
    int valor;
    bool hipotecada;
    int alquiler[4];
};

// OPERACIONES
Ferrocarril CrearFerrocarril(std::string, int, bool, int[4]);

#endif