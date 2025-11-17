#include "Partida.h"

#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>


int TirarDado() {
    return rand() % 6 + 1;
}

Partida DecidirOrdenUsuarios(User u1, User u2, User u3, User u4) {

    // Se guardan temporalmente para poder ordenarlos

    std::vector<User> usuarios = {u1, u2, u3, u4};

    for (auto &u : usuarios) {
        std::cout << "\nTurno para que " << u.name << " tire sus dados iniciales.\n";
        std::cout << "Presiona ENTER para tirar...";
        std::cin.get();

        int d1 = TirarDado();
        int d2 = TirarDado();
        u.posicion = d1 + d2;   

        std::cout << "  Dados: " << d1 << " + " << d2 
                  << " = " << u.posicion << "\n";
    }

    // Ordenar de mayor a menor según la suma 
    std::sort(usuarios.begin(), usuarios.end(),
              [](const User &a, const User &b) {
                  return a.posicion > b.posicion;
              });

    Partida p;
    p.nTurno = 1;

    // Pasar usuarios al map
    for (auto &u : usuarios)
        p.usuarios[u.name] = {u, {}};

    std::cout << "\nOrden final de jugadores:\n";
    for (auto &u : usuarios)
        std::cout << " - " << u.name << " (" << u.posicion << ")\n";

    return p;
}


Partida IniciarPartida(std::vector<User> listaUsuarios) {

    Partida p;

    p.nTurno = 1;
    p.tablero = CrearTablero();
    p.carcel = CrearCarcel();

    // Agregar los usuarios al map
    for (auto &u : listaUsuarios)
        p.usuarios[u.name] = {u, {}};

    std::cout << "Partida iniciada.\n";

    return p;
}
