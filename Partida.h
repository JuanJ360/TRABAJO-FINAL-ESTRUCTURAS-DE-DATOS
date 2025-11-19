#ifndef PARTIDA_H
#define PARTIDA_H

#include "User.h"
#include "Tablero.h"
#include "Banco.h"
#include "./casillas/Carcel.h"
#include "./casillas/Propiedad.h"

// estructura que representa una instancia de una partida de Monopoly
struct Partida {
    int nTurno = 0;

    // un solo registro de jugadores
    std::map<std::string, User> usuarios;
    std::vector<std::string> ordenUsuarios;
    Carcel carcel;
    Tablero tablero;
    Banco banco;
};

// OPERACIONES

void DecidirOrdenUsuarios(Partida &p);
Partida IniciarPartida(std::vector<User>); // función para instanciar el estado inicial de una partida
Partida AvanzarPartida(Partida); // función para crear una nueva instancia de la partida avanzando el turno
int TirarDado(); // función para tirar UN SOLO DADO

bool PropiedadPerteneceAAlguien(Partida, std::string); // función que recibe el nombre de una propiedad y devuelve el verdadero o falso si este pertenece o no pertenece a algun jugador
std::string DuenoDeLaPropiedad(Partida, std::string); // función que recibe el nombre de una propiedad y devuelve el nombre del propietario de dicha propiedad

Partida GanarPropiedad(Partida, User, Propiedad);
Partida GanarFerrocarril(Partida, User, Ferrocarril);
Partida GanarServicio(Partida, User, Servicio);

int numeroDeFerrocarriles(const Partida&, const std::string&); // función para saber cuantas propiedades de ferrocarril tiene un jugador
int NumeroDeServicios(const Partida&, const std::string&); // número de servicios que posee un jugador
int NumeroDePropiedades(const Partida&, const std::string&); // número de propiedades que posee un jugador

Partida SubastarPropiedad(Partida, std::string, std::string); // nombre de la propiedad y a quien se subasta para darle dicha propiedad

User AvanzarJugador(User&); // recibe el nombre del jugador
bool TresParesConsecutivos(User&); // para comprobar después de cada tirada de los dados del jugador si este ha sacado 3 pares consecutivos

void ReglaTercerTurnoCarcel(Carcel&, std::string); // la regla de los 3 turnos en la carcel
void ReglaTercerParFuera(Carcel&, std::string); // la misma regla de los 3 Pares pero cuando estamos afuera, para entrar a la carcel

User UsarCarta(User, CartaSuerte);

std::string PropietarioDeServicio(Partida&, const std::string);
std::string PropietarioDeFerrocarril(Partida&, const std::string);
std::string PropietarioDePropiedad(Partida&, const std::string);
bool PropiedadEnMonopolio(Partida&, const std::string);
void EjecutarCasilla(Partida&, User&, int);

#endif