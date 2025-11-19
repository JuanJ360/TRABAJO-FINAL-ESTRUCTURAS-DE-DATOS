// Monopoly.cpp
#include "Monopoly.h"
#include <iostream>


void Monopoly::mostrarMenuPrincipal() {
    int opcion;

    while (true) {
        std::cout << "\n===== MENU PRINCIPAL MONOPOLY =====\n";
        std::cout << "1. Iniciar nueva partida\n";
        std::cout << "2. Mostrar estado de la partida\n";
        std::cout << "3. Jugar turno\n";
        std::cout << "4. Salir";
        std::cout << "\n Selecciona una opcion: ";
        
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                iniciarNuevaPartida();
                break;

            case 2:
                mostrarEstadoPartida();
                break;

            case 3:
                jugarTurno();
                break;

            case 4:
                std::cout << "Saliendo del juego...\n";
                return;

            default:
                std::cout << "Opción inválida.\n";
        }
    }
}

void Monopoly::iniciarNuevaPartida() {
    std::cout << "\n--- Iniciar Nueva Partida ---\n";

    std::vector<User> jugadores;

    for (int i = 1; i <= 4; i++) {
        std::string nombre;
        std::cout << "Nombre del jugador " << i << ": ";
        std::cin >> nombre;
        jugadores.push_back(CrearUsuario(nombre));
    }

    //crear la partida
    partidaActual = IniciarPartida(jugadores);

    // Luego decidir el orden
    DecidirOrdenUsuarios(partidaActual);

    juegoIniciado = true;

    std::cout << "\nPartida creada.\n";
}

void Monopoly::mostrarEstadoPartida() {
    if (!juegoIniciado) {
        std::cout << "No hay una partida iniciada.\n";
        return;
    }

    std::cout << "\n--- ESTADO DE LA PARTIDA ---\n";

    for (const auto &entry : partidaActual.usuarios) {
        const std::string &nombre = entry.first;
        const User &user = entry.second;

        std::cout << "\nJugador: " << nombre << "\n";
        std::cout << "  Dinero: $" << user.cash << "\n";
        std::cout << "  Posicion: " << user.posicion << "\n";

        std::cout << "  Propiedades: ";
        if (user.propiedades.empty()) std::cout << "Ninguna";
        for (const auto &p : user.propiedades) std::cout << p.nombre << ", ";
        std::cout << "\n";

        std::cout << "  Servicios: ";
        if (user.servicios.empty()) std::cout << "Ninguno";
        for (const auto &s : user.servicios) std::cout << s.nombre << ", ";
        std::cout << "\n";

        std::cout << "  Ferrocarriles: ";
        if (user.ferrocarriles.empty()) std::cout << "Ninguno";
        for (const auto &f : user.ferrocarriles) std::cout << f.nombre << ", ";
        std::cout << "\n";
    }
}
void Monopoly::jugarTurno() {
    if (!juegoIniciado) {
        std::cout << "No hay una partida iniciada.\n";
        return;
    }

    // Si no hay jugadores registrados, error
    if (partidaActual.ordenUsuarios.empty()) {
        std::cout << "ERROR: No hay jugadores en la partida.\n";
        return;
    }

    // Obtener índice de turno actual
    int idx = partidaActual.nTurno;

    // Seguridad: si el índice se sale, se resetea
    if (idx >= (int)partidaActual.ordenUsuarios.size()) {
        partidaActual.nTurno = 0;
        idx = 0;
    }

    // Nombre del jugador que va
    std::string nombreJugador = partidaActual.ordenUsuarios[idx];

    // Referencia al jugador
    User& jugador = partidaActual.usuarios[nombreJugador];

    std::cout << "\n===== TURNO DE " << nombreJugador << " =====\n";

    // Avanzar al jugador (tirar dados y mover)
    AvanzarJugador(jugador);

    // Pasar al siguiente turno
    partidaActual.nTurno = (partidaActual.nTurno + 1) % partidaActual.ordenUsuarios.size();

    std::cout << "Turno terminado. El siguiente jugador será "<< partidaActual.ordenUsuarios[partidaActual.nTurno]<< ".\n";
}
