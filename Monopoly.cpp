// Monopoly.cpp
#include "Monopoly.h"
#include <iostream>

using namespace std;

void Monopoly::mostrarMenuPrincipal() {
    int opcion;

    while (true) {
        cout << "\n===== MENU PRINCIPAL MONOPOLY =====\n";
        cout << "1. Iniciar nueva partida\n";
        cout << "2. Mostrar estado de la partida\n";
        cout << "3. Jugar turno\n";
        cout << "4. Salir\n";
        cout << "Selecciona una opcion: ";

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
                cout << "Saliendo del juego...\n";
                return;

            default:
                cout << "Opción inválida.\n";
        }
    }
}

void Monopoly::iniciarNuevaPartida() {
    cout << "\n--- Iniciar Nueva Partida ---\n";

    int n;
    cout << "¿Cuántos jugadores? (mínimo 2, máximo 4): ";
    if (!(cin >> n)) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Número inválido.\n";
        return;
    }

    if (n < 2 || n > 4) {
        cout << "Número inválido.\n";
        return;
    }

    vector<User> jugadores;
    jugadores.reserve(n);

    for (int i = 1; i <= n; i++) {
        string nombre;
        cout << "Nombre del jugador " << i << ": ";
        cin >> ws;
        getline(cin, nombre);
        if (nombre.empty()) {
            cout << "Nombre vacío, usando Jugador" << i << "\n";
            nombre = "Jugador" + to_string(i);
        }
        // usa la función que ya tienes para inicializar un User
        jugadores.push_back(CrearUsuario(nombre));
    }

    partidaActual = IniciarPartida(jugadores);
    juegoIniciado = true;

    cout << "La partida ha sido creada exitosamente.\n";
}

void Monopoly::mostrarEstadoPartida() {
    if (!juegoIniciado) {
        cout << "No hay una partida iniciada.\n";
        return;
    }

    cout << "\n--- ESTADO DE LA PARTIDA ---\n";

    // Recorremos el map central de usuarios
    for (const auto &entry : partidaActual.usuarios) {
        const string &nombre = entry.first;
        const User &user = entry.second;

        cout << "\nJugador: " << nombre << "\n";
        cout << "  Dinero: $" << user.cash << "\n";
        cout << "  Posicion: " << user.posicion << "\n";

        cout << "  Propiedades: ";
        if (user.propiedades.empty()) cout << "Ninguna";
        for (const auto &p : user.propiedades) cout << p.nombre << ", ";
        cout << "\n";

        cout << "  Servicios: ";
        if (user.servicios.empty()) cout << "Ninguno";
        for (const auto &s : user.servicios) cout << s.nombre << ", ";
        cout << "\n";

        cout << "  Ferrocarriles: ";
        if (user.ferrocarriles.empty()) cout << "Ninguno";
        for (const auto &f : user.ferrocarriles) cout << f.nombre << ", ";
        cout << "\n";
    }
}

void Monopoly::jugarTurno() {
    if (!juegoIniciado) {
        cout << "No hay una partida iniciada.\n";
        return;
    }

    cout << "\n--- Jugar turno (pendiente de implementación completa) ---\n";
    cout << "Esta acción será implementada por la lógica principal de Partida/Turnos.\n";
}
