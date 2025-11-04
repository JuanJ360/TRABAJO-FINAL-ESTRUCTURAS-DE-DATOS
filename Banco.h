#ifndef BANCO_H
#define BANCO_H

#include "User.h"
#include "casillas/Propiedad.h"

struct Banco {
    int dinero;
    std::vector<Propiedad> propiedades;
};

Banco crearBanco(int, std::vector<Propiedad>);


#endif