#ifndef CARTA_SUERTE_H
#define CARTA_SUERTE_H

#include <string>
#include <queue>
#include <vector>
#include <fstream> // para leer el archivo json
#include <algorithm>
#include <random>

#include "../viernes13/json.hpp"

using json = nlohmann::json;

struct CartaSuerte {
    std::string nombre;
    std::string tipo;
    std::string mensaje;
};

CartaSuerte CrearCartaSuerte(std::string, std::string, std::string);
std::queue<CartaSuerte> GenerarColaCartasSuerte(); // no se bien si esta función deberia de colocarse aqui o deberia de estar en una estructura de mayor grado (que contenga o use las cartas de la suerte)

#endif