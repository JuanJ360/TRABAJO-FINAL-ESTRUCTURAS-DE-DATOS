#ifndef MONOPOLY_H
#define MONOPOLY_H

#include <vector>
#include "Partida.h"
#include "User.h"

struct Monopoly {

    // --- Estado del juego ---
    bool juegoIniciado = false;
    Partida partidaActual;

    // --- Funcionalidades del menú ---
    void mostrarMenuPrincipal(); 
    void iniciarNuevaPartida();  
    void mostrarEstadoPartida(); 
    void jugarTurno();          
};

#endif
