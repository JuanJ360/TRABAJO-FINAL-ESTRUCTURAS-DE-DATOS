#ifndef TABLERO_H
#define TABLERO_H

#include <cstdlib>
#include <vector>
#include <string>
#include <utility>
#include <fstream>

#include "User.h"
#include "./casillas/Ferrocarril.h"
#include "./casillas/Servicio.h"
#include "./casillas/Propiedad.h"
#include "./casillas/Casilla.h"
#include "viernes13/json.hpp"

using json = nlohmann::json;

struct Tablero {
    std::vector<Casilla> casillas; // el tipo de la casilla y la posición dentro de su respectivo vector segun su tipo
    std::vector<Ferrocarril> ferrocarriles;
    std::vector<Propiedad> propiedades;
    std::vector<Servicio> servicios;
    std::vector<std::string> especiales; // carcel o casillas de suerte (supongo)
};

Tablero CrearTablero();
Casilla ObtenerCasilla(const Tablero&, int); 
void VaciarTablero(Tablero&);
void EjecutarCasilla(const Tablero&, User);

#endif