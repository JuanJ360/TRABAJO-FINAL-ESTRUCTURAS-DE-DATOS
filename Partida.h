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

void AsignarPropiedad(Partida&, const std::string&, const std::string&, int);

int numeroDeFerrocarriles(const Partida&, const std::string&); // función para saber cuantas propiedades de ferrocarril tiene un jugador
int NumeroDeServicios(const Partida&, const std::string&); // número de servicios que posee un jugador
int NumeroDePropiedades(const Partida&, const std::string&); // número de propiedades que posee un jugador

Partida SubastarPropiedad(Partida, std::string, std::string); // nombre de la propiedad y a quien se subasta para darle dicha propiedad

void AvanzarJugador(Partida& p, User& jugador); // recibe el nombre del jugador


void ReglaTercerTurnoCarcel(Carcel&, const std::string&); // la regla de los 3 turnos en la carcel
void ReglaTercerParFuera(Carcel&, User&);// la misma regla de los 3 Pares pero cuando estamos afuera, para entrar a la carcel

User UsarCarta(User, CartaSuerte);

std::string PropietarioDeServicio(Partida&, const std::string);
std::string PropietarioDeFerrocarril(Partida&, const std::string);
std::string PropietarioDePropiedad(Partida&, const std::string);
bool PropiedadEnMonopolio(Partida&, const std::string);
void EjecutarCasilla(Partida&, User&, int);
void SubastarPropiedad(Partida&, User&, std::string, bool); // usuario que no participa de la subasta y el nombre de la propiedad

#endif