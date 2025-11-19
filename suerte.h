#ifndef SUERTE_H
#define SUERTE_H

#include <vector>
#include <queue>
#include <algorithm>
#include <random>
#include <fstream>
#include "viernes13/json.hpp"
#include "cartas/CartaSuerte.h"  // trabajar con json

using json = nlohmann::json;

struct Suerte {
    std::queue<CartaSuerte> colaCartas;
};

Suerte IniciarSuerte();
CartaSuerte SacarCartaSuerte(Suerte&);

#endif
