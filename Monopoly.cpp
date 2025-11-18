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
        cin >> opcion;

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
    cin >> n;

    if (n < 2 || n > 4) {
        cout << "Número inválido.\n";
        return;
    }

    vector<User> jugadores;
    jugadores.reserve(n);

    for (int i = 1; i <= n; i++) {
        string nombre;
        cout << "Nombre del jugador " << i << ": ";
        cin >> nombre;

        User u;
        u.name = nombre;
        jugadores.push_back(u);
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

    for (auto &par : partidaActual.usuariosProp) {
        const string &nombre = par.first;
        const auto &user = par.second.first;
        const auto &props = par.second.second;

        cout << "\nJugador: " << nombre << "\n";
        cout << "Propiedades: ";
        if (props.empty()) cout << "Ninguna";
        for (const auto &p : props) cout << p.nombre << ", ";
        cout << "\n";
    }

    for (auto &par : partidaActual.usuariosSer) {
        const string &nombre = par.first;
        const auto &sers = par.second.second;

        cout << "Servicios: ";
        if (sers.empty()) cout << "Ninguno";
        for (const auto &s : sers) cout << s.nombre << ", ";
        cout << "\n";
    }

    for (auto &par : partidaActual.usuariosFerro) {
        const string &fers = par.second.second;

        cout << "Ferrocarriles: ";
        if (fers.empty()) cout << "Ninguno";
        for (const auto &f : fers) cout << f.nombre << ", ";
        cout << "\n";
    }
}


void Monopoly::jugarTurno() {
    if (!juegoIniciado) {
        cout << "No hay una partida iniciada.\n";
        return;
    }

    cout << "\n--- Jugar turno---\n"; // Pendiente de implmenentar teniendo en cuenta que faltan cosas de partida
}
