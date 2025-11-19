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
};

#endif