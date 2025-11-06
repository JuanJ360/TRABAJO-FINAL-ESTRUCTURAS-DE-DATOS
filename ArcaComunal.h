#ifndef ARCA_COMUNAL_H
#define ARCA_COMUNAL_H

#include <vector>
#include <queue>
#include <algorithm>
#include <random>
#include <fstream> // para leer el archivo json
#include "viernes13/json.hpp"
#include "cartas/CartaArcaComunal.h" // para trabajar con los json

using json = nlohmann::json;

struct ArcaComunal {
    std::queue<CartaArcaComunal> colaCartas;
};

// std::vector<CartaArcaComunal> BarajarCartas(std::vector<CartaArcaComunal>);
ArcaComunal IniciarArcaComunal();
CartaArcaComunal SacarCartaArcaComunal(ArcaComunal&);

#endif