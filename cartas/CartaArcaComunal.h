#ifndef CARTA_ARCA_COMUNAL_H
#define CARTA_ARCA_COMUNAL_H


#include <string>
#include <queue>
#include <vector>
#include <fstream> // para leer el archivo json
#include <algorithm>
#include <random>

#include "../viernes13/json.hpp"

using json = nlohmann::json;


struct CartaArcaComunal {
    std::string tipo;
    std::string nombre;
    std::string mensaje;
};

CartaArcaComunal CrearCartaArcaComunal(std::string, std::string, std::string);
std::queue<CartaArcaComunal> GenerarColaCartasArcaComunal();

#endif