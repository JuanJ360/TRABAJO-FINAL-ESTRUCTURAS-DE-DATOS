// Monopoly.cpp
#include "Monopoly.h"
#include <iostream>
#include <algorithm>

void Monopoly::mostrarMenuPrincipal() {
    int opcion;

    while (true) {
        std::cout << "\n===== MENU PRINCIPAL MONOPOLY =====\n";
        std::cout << "1. Iniciar nueva partida\n";
        std::cout << "2. Mostrar estado de la partida\n";
        std::cout << "3. Jugar turno\n";
        std::cout << "4. Deshacer ultimo turno\n";
        std::cout << "5. Ver historial de turnos\n";
        std::cout << "6. Salir\n";
        std::cout << "Selecciona una opcion: ";
        
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
                DevolverPartida();
                break;

            case 5:
                VerHistorial();
                break;

            case 6:
                std::cout << "Saliendo del juego...\n";
                return;

            default:
                std::cout << "Opcion invalida.\n";
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

    partidaActual = IniciarPartida(jugadores);

    DecidirOrdenUsuarios(partidaActual);

    // Limpiar historial de partidas anteriores
    while (!partidas.empty()) {
        partidas.pop();
    }

    juegoIniciado = true;

    std::cout << "\nPartida creada.\n";
}

void Monopoly::mostrarEstadoPartida() {
    if (!juegoIniciado) {
        std::cout << "No hay una partida iniciada.\n";
        return;
    }

    std::cout << "\n--- ESTADO DE LA PARTIDA ---\n";
    std::cout << "Turno actual: " << partidaActual.ordenUsuarios[partidaActual.nTurno] << "\n";
    std::cout << "Turnos guardados: " << partidas.size() << "\n\n";

    for (const auto &entry : partidaActual.usuarios) {
        const std::string &nombre = entry.first;
        const User &user = entry.second;

        std::cout << "Jugador: " << nombre << "\n";
        std::cout << "  Dinero: $" << user.cash << "\n";
        std::cout << "  Posicion: " << user.posicion << "\n";

        std::cout << "  Propiedades: ";
        if (user.propiedades.empty()) {
            std::cout << "Ninguna";
        } else {
            for (const auto &p : user.propiedades) {
                std::cout << p.nombre << ", ";
            }
        }
        std::cout << "\n";

        std::cout << "  Servicios: ";
        if (user.servicios.empty()) {
            std::cout << "Ninguno";
        } else {
            for (const auto &s : user.servicios) {
                std::cout << s.nombre << ", ";
            }
        }
        std::cout << "\n";

        std::cout << "  Ferrocarriles: ";
        if (user.ferrocarriles.empty()) {
            std::cout << "Ninguno";
        } else {
            for (const auto &f : user.ferrocarriles) {
                std::cout << f.nombre << ", ";
            }
        }
        std::cout << "\n\n";
    }
}

void Monopoly::GuardarEstadoPartida() {
    // Asegurarse de que el usuario actual está sincronizado
    int idx = partidaActual.nTurno;
    if (idx < (int)partidaActual.ordenUsuarios.size()) {
        std::string nombreJugador = partidaActual.ordenUsuarios[idx];
        // El usuario ya debe estar en partidaActual.usuarios
    }
    
    // Guardar la partida completa con todos los usuarios actualizados
    partidas.push(partidaActual);
}

void Monopoly::jugarTurno() {
    if (!juegoIniciado) {
        std::cout << "No hay una partida iniciada.\n";
        return;
    }

    if (partidaActual.ordenUsuarios.empty()) {
        std::cout << "ERROR: No hay jugadores en la partida.\n";
        return;
    }

    // PASO 1: GUARDAR EL ESTADO ACTUAL ANTES DE JUGAR EL TURNO
    GuardarEstadoPartida();

    // PASO 2: EJECUTAR EL TURNO NORMAL
    int idx = partidaActual.nTurno;

    if (idx >= (int)partidaActual.ordenUsuarios.size()) {
        partidaActual.nTurno = 0;
        idx = 0;
    }

    std::string nombreJugador = partidaActual.ordenUsuarios[idx];
    User& jugador = partidaActual.usuarios[nombreJugador];

    std::cout << "\n===== TURNO DE " << nombreJugador << " =====\n";

    AvanzarJugador(partidaActual, jugador);

    // Actualizar el usuario en la partida después del turno
    partidaActual.usuarios[nombreJugador] = jugador;

    // Pasar al siguiente turno
    partidaActual.nTurno = (partidaActual.nTurno + 1) % partidaActual.ordenUsuarios.size();

    std::cout << "Turno terminado. El siguiente jugador sera " 
              << partidaActual.ordenUsuarios[partidaActual.nTurno] << ".\n";
}

void Monopoly::DevolverPartida() {
    if (partidas.empty()) {
        std::cout << "No hay turnos anteriores para deshacer.\n";
        return;
    }

    std::cout << "\n--- Deshaciendo Ultimo Turno ---\n";
    
    // Obtener el nombre del jugador cuyo turno se va a deshacer
    std::string nombreJugadorAnterior = partidaActual.ordenUsuarios[partidaActual.nTurno];
    
    // Calcular el indice del jugador anterior
    int idxAnterior;
    if (partidaActual.nTurno == 0) {
        idxAnterior = partidaActual.ordenUsuarios.size() - 1;
    } else {
        idxAnterior = partidaActual.nTurno - 1;
    }
    std::string nombreJugadorQueTuvo = partidaActual.ordenUsuarios[idxAnterior];

    std::cout << "Se va a deshacer el turno de " << nombreJugadorQueTuvo << ".\n";
    std::cout << "Estas seguro? (si/no): ";
    
    std::string confirmacion;
    std::cin >> confirmacion;
    
    // Normalizar respuesta
    std::transform(confirmacion.begin(), confirmacion.end(), confirmacion.begin(), ::tolower);
    
    if (confirmacion != "si") {
        std::cout << "Operacion cancelada.\n";
        return;
    }

    // Restaurar la partida anterior
    partidaActual = partidas.top();
    partidas.pop();

    // El nTurno ya está correcto en la partida restaurada

    std::cout << "\nX Partida restaurada.\n";
    std::cout << "X Estado anterior al turno de " << nombreJugadorQueTuvo << " restaurado.\n";
    std::cout << "X Proximo turno: " << partidaActual.ordenUsuarios[partidaActual.nTurno] << "\n\n";
}

void Monopoly::VerHistorial() {
    std::cout << "\n--- HISTORIAL DE TURNOS ---\n";
    std::cout << "Turnos guardados en el historial: " << partidas.size() << "\n";
    
    if (partidas.empty()) {
        std::cout << "No hay turnos guardados aun.\n";
        return;
    }

    std::cout << "Puedes deshacer hasta " << partidas.size() << " turno(s).\n";
    std::cout << "Usa la opcion 'Deshacer ultimo turno' para volver atras.\n";
}