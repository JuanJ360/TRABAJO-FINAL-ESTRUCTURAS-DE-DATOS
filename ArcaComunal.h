#ifndef ARCA_COMUNAL_H
#define ARCA_COMUNAL_H

#include <vector>
#include <queue>
#include <algorithm>
#include <random>
#include "cartas/CartaArcaComunal.h"

struct ArcaComunal {
    std::queue<CartaArcaComunal> colaCartas;
};

// std::vector<CartaArcaComunal> BarajarCartas(std::vector<CartaArcaComunal>);
ArcaComunal IniciarArcaComunal();
CartaArcaComunal SacarCartaArcaComunal(ArcaComunal&);

#endif