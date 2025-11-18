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

// OPERACIONES

Partida DecidirOrdenUsuarios(User, User, User, User);
Partida IniciarPartida(std::vector<User>); // función para instanciar el estado inicial de una partida
Partida AvanzarPartida(Partida); // función para crear una nueva instancia de la partida avanzando el turno
int TirarDado(); // función para tirar UN SOLO DADO
bool PropiedadPerteneceAAlguien(Partida, std::string); // función que recibe el nombre de una propiedad y devuelve el verdadero o falso si este pertenece o no pertenece a algun jugador
std::string DuenoDeLaPropiedad(Partida, std::string); // función que recibe el nombre de una propiedad y devuelve el nombre del propietario de dicha propiedad

void ReglaTercerTurno(Carcel&, std::string); // la regla de los 3 turnos en la carcel
User AvanzarJugador(Tablero, User); // recibe el nombre del jugador
bool TresParesConsecutivos(User&); // para comprobar después de cada tirada de los dados del jugador si este ha sacado 3 pares consecutivos

int numeroDeFerrocarriles(Partida, std::string); // función para saber cuantas propiedades de ferrocarril tiene un jugador
int NumeroDeServicios(const Tablero&, std::string); // número de servicios que posee un jugador
int NumeroDePropiedades(const Tablero&, std::string); 

Partida GanarPropiedad(Partida, User, Propiedad);
Partida SubastarPropiedad(Partida, std::string, std::string); // nombre de la propiedad y a quien se subasta para darle dicha propiedad
User UsarCarta(User, CartaSuerte);

#endif