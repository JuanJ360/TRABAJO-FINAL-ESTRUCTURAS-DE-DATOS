#ifndef BANCO_H
#define BANCO_H

#include "User.h"
#include "casillas/Propiedad.h"

struct Banco {
    // int dinero; en verdad el banco tiene dinero infinito por lo que a pesar de que en el juego fisico el dinero es finito porque no se puen tener infinitos billetes entonces no es necesario este dato
    std::vector<Propiedad> propiedades;
};

Banco crearBanco(std::vector<Propiedad>);


#endif