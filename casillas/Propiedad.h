#ifndef PROPIEDAD_H
#define PROPIEDAD_H

#include <string>
#include <vector>

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
};

// OPERACIONES
Propiedad CrearPropiedad(std::string, std::string, std::string, bool, int, int[6], int, int, int, int);
int ValorRentaPropiedad(bool, std::string); // color de propiedad x 

#endif