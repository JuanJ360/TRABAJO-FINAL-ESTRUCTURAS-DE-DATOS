#ifndef FERROCARRIL_H
#define FERROCARRIL_H

#include <string>
#include <stdexcept>
#include <math.h>

struct Ferrocarril {
    std::string tipo;
    std::string nombre;
    int valor;
    bool hipotecada;
    int alquiler[4];
};

// OPERACIONES
Ferrocarril CrearFerrocarril(std::string, int, bool, int[4]);
int ValorFerrocarril(int); // recibe el numero de ferrocarriles del dueño de la casilla y devuelve el valor a pagarle

#endif