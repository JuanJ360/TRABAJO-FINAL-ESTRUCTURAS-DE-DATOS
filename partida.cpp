#include "Partida.h"

#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>


int TirarDado() {
    return rand() % 6 + 1;
}

Partida DecidirOrdenUsuarios(User u1, User u2, User u3, User u4) {

    // Se guardan los usuarios en un vector temporal para organizarlos

    std::vector<User> usuarios = {u1, u2, u3, u4};

    for (auto &u : usuarios) {
        std::cout << "Turno para que " << u.name << " tire su dado inicial\n";
        std::cout << "Presiona enter para tirar";
        std::cin.get();
        u.sumDados = TirarDado();
        std::cout << " -> " << u.sumDados << "\n";
    }

    // Ordenar según el dado inicial
    std::sort(usuarios.begin(), usuarios.end(),
              [](const User &a, const User &b) {
                  return a.sumDados > b.sumDados;
              });

    Partida p;
    p.nTurno = 1;

    // Llenar usuarios
    for (auto &u : usuarios)
        p.usuarios[u.name] = {u, {}};

    std::cout << "\nOrden final:\n";
    for (auto &u : usuarios)
        std::cout << " - " << u.name << "\n";

    return p;
}


Partida IniciarPartida(std::vector<User> listaUsuarios) {

    Partida p;

    p.nTurno = 1;
    p.tablero = CrearTablero();
    p.carcel = CrearCarcel();

    for (auto &u : listaUsuarios)
        p.usuarios[u.name] = {u, {}};

    std::cout << "Partida iniciada.";

    return p;
}
