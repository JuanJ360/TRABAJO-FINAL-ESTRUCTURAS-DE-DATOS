#ifndef TABLERO_H
#define TABLERO_H

#include <cstdlib>
#include <vector>
#include <string>
#include <utility>

//#include "Casilla.h"
#include "./casillas/Ferrocarril.h"
#include "./casillas/Servicio.h"
#include "./casillas/Propiedad.h"

struct Tablero {
    std::vector<std::pair<std::string, int>> casillas; // el tipo de la casilla y la posición dentro de su respectivo vector segun su tipo
    std::vector<Ferrocarril> ferrocarriles;
    std::vector<Propiedad> propiedades;
    std::vector<Servicio> servicios;
    std::vector<std::string> especiales; // carcel o casillas de suerte (supongo)
};

Tablero CrearTablero();
std::string ObtenerCasilla(const Tablero&, int);
void VaciarTablero(Tablero&);

#endif