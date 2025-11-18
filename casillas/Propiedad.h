#ifndef PROPIEDAD_H
#define PROPIEDAD_H

#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>

struct Propiedad {
    std::string tipo;
    std::string subTipo;
    std::string name;
    std::string color;
    int precio;
    bool hipotecada;
    int alquiler[6]; // alquiler[0] -> sin casas, alquiler entre 1 y 4 -> con casas, alquiler[5] -> con hotel
    int valorCasa;
    int valorHotel;
    int valorHipotecar;
    int valorDesHipotecar;
    // falta
    int numCasas;
    int numHoteles;
};

// OPERACIONES
Propiedad CrearPropiedad(std::string, std::string, std::string, bool, int, int[6], int, int, int, int);
Propiedad ConstruirNCasas(Propiedad, int); // propiedad x numero de casas
Propiedad ConsturirHotel(Propiedad); // propiedad
int ValorRentaPropiedad(Propiedad&, bool); // propiedad x esta en un monopolio

#endif