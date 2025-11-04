#ifndef PARTIDA_H
#define PARTIDA_H

#include "User.h"
#include "Tablero.h"
#include "Banco.h"
#include "./casillas/Carcel.h"
#include "./casillas/Propiedad.h"

// estructura que representa una instancia de una partida de Monopoly
struct Partida {
    int nTurno; // numero de turno
    std::map<std::string, std::pair<User, std::vector<Propiedad>>> usuarios; // userName: {user, < propiedades del user >}
    Carcel carcel;
    Tablero tablero;
    Banco banco;
};

Partida IniciarPartida(); // función para instanciar el estado inicial de una partida
Partida AvanzarPartida(Partida); // función para crear una nueva instancia de la partida avanzando el turno
void GanarPropiedad(User&, Propiedad);
void ReglaTercerTurno(Carcel&, std::string); // la regla de los 3 turnos en la carcel
int TirarDado(); // función para tirar UN SOLO DADO
void AvanzarJugador(User); // resibe el nombre del jugador
int numeroDeServicios(User); // número de servicios que posee un jugador

#endif