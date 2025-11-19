#ifndef MONOPOLY_H
#define MONOPOLY_H

#include <vector>
#include <stack>
#include "Partida.h"
#include "User.h"

struct Monopoly {
    // --- Estado del juego ---
    bool juegoIniciado = false;
    Partida partidaActual;
    std::stack<Partida> partidas;  // Historial de partidas para deshacer

    // --- Funcionalidades del menú ---
    void mostrarMenuPrincipal(); 
    void iniciarNuevaPartida();  
    void mostrarEstadoPartida(); 
    void jugarTurno();
    void DevolverPartida();
    void GuardarEstadoPartida();
    void VerHistorial();

    // --- Menú de propiedades ---
    void MenuPropiedades(); // muestra el menú para el jugador del turno actual
    void MostrarPropiedadesJugador(const std::string& jugador);

    // Operaciones de propiedad
    bool ComprarCasa(const std::string& jugador, const std::string& nombreProp);
    bool ComprarHotel(const std::string& jugador, const std::string& nombreProp);
    bool VenderCasa(const std::string& jugador, const std::string& nombreProp);
    bool VenderHotel(const std::string& jugador, const std::string& nombreProp);
    bool HipotecarPropiedad(const std::string& jugador, const std::string& nombreProp);
    bool DeshipotecarPropiedad(const std::string& jugador, const std::string& nombreProp);

    std::vector<Propiedad*> ObtenerPropsColor(Partida& p, const std::string& color, const std::string& jugador);
    bool TieneMonopolio(Partida& p, const std::string& jugador, const std::string& color);
    bool PuedeConstruirCasa(Partida& p, const std::string& jugador, Propiedad& prop);
    bool PuedeConstruirHotel(Partida& p, const std::string& jugador, Propiedad& prop);

};

#endif