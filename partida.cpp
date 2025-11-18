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
    std::sort(usuarios.begin(), usuarios.end(),[](const User &a, const User &b) {
                  return a.posicion > b.posicion;});

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

bool PropiedadPerteneceAAlguien(Partida p, std::string nombrePropiedad) {

    for (const auto &par : p.usuarios) {

        const auto &listaProps = par.second.second; 
        // par.second = {User, vector<Propiedad>}
        // par.second.second = vector<Propiedad>

        // Buscar en las propiedades del jugador
        for (const auto &prop : listaProps) {
            if (prop.nombre == nombrePropiedad) {
                return true; 
            }
        }
    }


    return false;
}

std::string DuenoDeLaPropiedad(Partida p, std::string nombrePropiedad) {

    for (const auto &par : p.usuarios) {

        const std::string &nombreJugador = par.first;
        const auto &listaProps = par.second.second;

        for (const auto &prop : listaProps) {
            if (prop.nombre == nombrePropiedad) {
                return nombreJugador; // lo encontramos
            }
        }
    }

    // Si no la tiene nadie
    return "Nadie";
}

Partida GanarPropiedad(Partida p, User u, Propiedad propiedad) {

    // acceso con el map
    auto it = p.usuarios.find(u.name);

    if (it == p.usuarios.end()) {
        std::cout << "Error: el jugador " << u.name << " no existe en la partida.\n";
        return p;
    }

    // Agregar la propiedad al vector del jugador
    it->second.second.push_back(propiedad);

    // Actualizar el objeto User dentro de la partida
    it->second.first = u;

    std::cout << ">>> " << u.name << " ha ganado la propiedad: " 
              << propiedad.name << "\n";

    return p;
}


User AvanzarJugador(User& jugador) {

    std::cout << "\nTurno de " << jugador.name << ". Presiona ENTER para tirar los dados...";
    std::cin.get();

    int d1 = TirarDado();
    int d2 = TirarDado();
    int suma = d1 + d2;

    std::cout << "  Dados: " << d1 << " + " << d2 << " = " << suma << "\n";

    // Avanzar posición
    int posicionAnterior = jugador.posicion;
    jugador.posicion = (jugador.posicion + suma) % 40;   // tablero de 40 casillas

    // Pasó por la salida
    if (posicionAnterior + suma >= 40) {
        std::cout << ">>> " << jugador.name << " pasó por la salida y recibe $200.\n";
        jugador.cash += 200;
    }

    std::cout << jugador.name << " ahora está en la casilla " << jugador.posicion << ".\n";

    return jugador;
}

void ReglaTercerTurnoCarcel(Carcel& carcel, const std::string& name) {
    
    // Obtener referencia al par <User*, turnos>
    auto& data = carcel.prisioneros[name];
    User* user = data.first;
    int turnos = data.second;

    // Si ya cumplió 3 turnos debe ser liberado
    if (turnos >= 3) {
        std::cout << user->name << " ha cumplido 3 turnos en la cárcel. Queda libre.\n";

        // Sale de la cárcel
        LiberarDeLaCarcel(carcel, name);

        // el user sale a casilla #10
        user->posicion = 10;

        // Resetear pares 
        user->contPares = 0;
    }
}

void ReglaTercerParFuera(Carcel& carcel, User& user) {
    if (!EstaArrestado(carcel, user.name) && user.contPares >= 3) {
        std::cout << user.name << " ha sacado 3 pares consecutivos. Va a la cárcel.\n";

        user.posicion = 10;
        user.contPares = 0;

        Arrestar(carcel, &user);
    }
}

bool TresParesConsecutivos(User& user) {

    if (user.contPares >= 3)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
