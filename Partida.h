#ifndef PARTIDA_H
#define PARTIDA_H

#include "User.h"
#include "Tablero.h"
#include "./casillas/Carcel.h"
#include "./casillas/Propiedad.h"


// estructura que representa una instancia de una partida de Monopoly
struct Partida {
    int nTurno; // numero de turno
    std::vector<User> jugadores;
    Carcel carcel;
    std::map<std::string, Propiedad> userPropiedades;
    Tablero tablero;
};

Partida IniciarPartida(); // función para instanciar el estado inicial de una partida
Partida AvanzarPartida(Partida); // función para crear una nueva instancia de la partida avanzando el turno 
void GanarPropiedad(User&, Propiedad);

#endif