#include "Partida.h"

#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>


int TirarDado() {
    return rand() % 6 + 1;
}


void DecidirOrdenUsuarios(Partida &p) {

    // Extraer los usuarios del map (copia)
    std::vector<User> usuarios;
    for (auto &kv : p.usuarios)
        usuarios.push_back(kv.second);

    std::cout << "\n--- Determinando orden de turnos ---\n";

    // Aqui se guardan las tiradas en una copia
    std::vector<std::pair<int, User>> tiradas;
    while (std::cin.get() != '\n');

    // Tirada inicial de cada jugador
    for (auto &u : usuarios) {
        std::cout << "\nTurno para que " << u.nombre << " tire sus dados iniciales.\n";
        std::cout << "Presiona ENTER para tirar...";
        std::string temp;
        std::getline(std::cin, temp);

        int d1 = TirarDado();
        int d2 = TirarDado();
        int suma = d1 + d2;

        std::cout << "  Dados: " << d1 << " + " << d2
                  << " = " << suma << "\n";

        // Nos quedamos con el usuario real sin cambiar su posición real
        u.posicion = 0;

        tiradas.push_back({suma, u});
    }

    // Ordenar por tirada (mayor a menor)
    std::sort(tiradas.begin(), tiradas.end(),
              [](const auto &a, const auto &b) {
                  return a.first > b.first;
              });

    // Limpiar orden antiguo
    p.ordenUsuarios.clear();

    // Actualizar el mapa de usuarios y el orden correcto
    for (auto &entry : tiradas) {
        const User &jug = entry.second;
        p.usuarios[jug.nombre] = jug;
        p.ordenUsuarios.push_back(jug.nombre);
    }

    // Reiniciamos el turno para que empiece desde el nuevo primero
    p.nTurno = 0;

    // Mostrar el orden final
    std::cout << "\nOrden final de jugadores:\n";
    for (auto &entry : tiradas) {
        std::cout << " - " << entry.second.nombre
                  << " (tiró " << entry.first << ")\n";
    }
}


Partida IniciarPartida(std::vector<User> listaUsuarios) {

    Partida p;

    p.nTurno = 0;
    p.tablero = CrearTablero();
    p.carcel = CrearCarcel();

    // Agregar los usuarios al map
    for (auto &u : listaUsuarios) {
        p.usuarios[u.nombre] = u;
        p.ordenUsuarios.push_back(u.nombre);
    }

    std::cout << "Partida iniciada.\n";

    return p;
}

bool PropiedadPerteneceAAlguien(Partida p, std::string nombrePropiedad) {

    for (const auto &par : p.usuarios) {
        const User& jugador = par.second;

        for (const auto &prop : jugador.propiedades)
            if (prop.nombre == nombrePropiedad)
                return true;
    }

    return false;
}

std::string DuenoDeLaPropiedad(Partida p, std::string nombrePropiedad) {

    for (const auto &par : p.usuarios) {
        const std::string& nombreJugador = par.first;
        const User& jugador = par.second;

        for (const auto &prop : jugador.propiedades)
            if (prop.nombre == nombrePropiedad)
                return nombreJugador;
    }

    return "Nadie";
}

Partida GanarPropiedad(Partida p, User u, Propiedad propiedad) {

    auto it = p.usuarios.find(u.nombre);

    if (it == p.usuarios.end()) {
        std::cout << "Error: jugador no existe.\n";
        return p;
    }

    // añadir al vector de propiedades del jugador
    it->second.propiedades.push_back(propiedad);

    return p;
}


User AvanzarJugador(User& jugador) {

    std::cout << "\nTurno de " << jugador.nombre << ". Presiona ENTER para tirar los dados...";
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
        std::cout << ">>> " << jugador.nombre << " pasó por la salida y recibe $200.\n";
        jugador.cash += 200;
    }

    std::cout << jugador.nombre << " ahora está en la casilla " << jugador.posicion << ".\n";

    return jugador;
}

void ReglaTercerTurnoCarcel(Carcel& carcel, const std::string& nombre) {
    
    // Obtener referencia al par <User*, turnos>
    auto& data = carcel.prisioneros[nombre];
    User* user = data.first;
    int turnos = data.second;

    // Si ya cumplió 3 turnos debe ser liberado
    if (turnos >= 3) {
        std::cout << user->nombre << " ha cumplido 3 turnos en la cárcel. Queda libre.\n";

        // Sale de la cárcel
        LiberarDeLaCarcel(carcel, nombre);

        // el user sale a casilla #10
        user->posicion = 10;

        // Resetear pares 
        user->contPares = 0;
    }
}

void ReglaTercerParFuera(Carcel& carcel, User& user) {
    if (!EstaArrestado(carcel, user.nombre) && user.contPares >= 3) {
        std::cout << user.nombre << " ha sacado 3 pares consecutivos. Va a la cárcel.\n";

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
int NumeroDePropiedades(const Partida& p, const std::string& jugador) {
    return p.usuarios.at(jugador).propiedades.size();
}

int NumeroDeServicios(const Partida& p, const std::string& jugador) {
    return p.usuarios.at(jugador).servicios.size();
}

int NumeroDeFerrocarriles(const Partida& p, const std::string& jugador) {
    return p.usuarios.at(jugador).ferrocarriles.size();
}

std::string PropietarioDeServicio(Partida& partida, const std::string nomServicio) {
    for(int i = 0; i < 4; i++) {
        User& user = partida.usuarios[partida.ordenUsuarios[i]];
        if (user.activo) {
            for (int j = 0; j < user.servicios.size(); j++) {
                if (user.servicios[j].nombre == nomServicio) {
                    return user.nombre;
                }
            }
        }
    }
    return "except";
}

std::string PropietarioDeFerrocarril(Partida& partida, const std::string nomFerrocarril) {
    for (int i = 0; i < 4; i++) {
        User& user = partida.usuarios[partida.ordenUsuarios[i]];
        if (user.activo) {
            for (int j = 0; j < user.ferrocarriles.size(); j++) {
                if (user.ferrocarriles[j].nombre == nomFerrocarril) {
                    return user.nombre;
                }
            }
        }
    }
    return "except";
}

std::string PropietarioDePropiedad(Partida& partida, const std::string nomPropiedad) {
    for (int i = 0; i < 4; i++) {
        User& user = partida.usuarios[partida.ordenUsuarios[i]];
        if (user.activo) {
            for (int j = 0; j < user.propiedades.size(); j++) {
                if (user.propiedades[j].nombre == nomPropiedad) {
                    return user.nombre;
                }
            }
        }
    }
    return "except";
}

// falta esta función
// un monopolio es cuando un jugador tiene todas las casillas de un mismo color
bool PropiedadEnMonopolio(Partida& partida, const std::string nomPropiedad) {
    return false; //falta por hacer

}

// adicionalmente hay que incorporarle el tema de las subastas
void EjecutarCasilla(Partida& partida, User& user, int tiradaDeDados) {
    Casilla cas = ObtenerCasilla(partida.tablero, user.posicion + tiradaDeDados);
    if (cas.tipo == "servicio") {
        Servicio& servi = partida.tablero.servicios[cas.indiceTipo];
        std::string propServi = PropietarioDeServicio(partida, servi.nombre);
        // la casilla no tiene dueño
        if (propServi == "except") {
            std::cout << user.nombre << " tiene " << user.cash << "$." << " Desea comprar la casilla " << servi.nombre << " por el modico precio de " << servi.valor << " ? (si o no)" << std::endl;
            std::string compCasilla;
            std::cin >> compCasilla;
            if (compCasilla == "si" || compCasilla == "SI" || compCasilla == "Si") {
                if (user.cash >= servi.valor) {
                    user = PerderDinero(user, servi.valor);
                    user.servicios.push_back(servi);
                    std::cout << user.nombre << " a comprado el servicio " << partida.tablero.servicios[cas.indiceTipo].nombre << "." << std::endl;
                    return;
                }
                else {
                    std::cout << user.nombre << " no tiene suficiente dinero y por ende se pasa a subastar." << std::endl;
                }
            }

            // aqui va la subasta del servicio
        }
        else if (propServi != user.nombre) {
            std::cout << user.nombre << " a caido en " << servi.nombre << ". Casilla la cual es propiedad de " << propServi << std::endl;
            int precio = ValorRentaServicio(tiradaDeDados, NumeroDeServicios(partida, propServi));
            partida.usuarios[propServi] = GanarDinero(partida.usuarios[propServi], precio);
            user = PerderDinero(user, precio);
            std::cout << user.nombre << " le ha pagado " << precio << " a " << propServi << ". " << user.nombre << " le quedan " << user.cash << "$" << std::endl;

            // falta manejar lo de que el usuario pueda quedarse sin dinero o en negativo y por ende deva de subastar o hipotecar
        }
    }

    else if (cas.tipo == "propiedad") {
        Propiedad& prop = partida.tablero.propiedades[cas.indiceTipo];
        std::string propProp = PropietarioDeFerrocarril(partida, prop.nombre);
        // la casilla no tiene dueño
        if (propProp == "except") {
            std::cout << user.nombre << " tiene " << user.cash << "$." << " Desea comprar la casilla " << prop.nombre << " por el modico precio de " << prop.precio << " ? (si o no)" << std::endl;
            std::string compCasilla;
            std::cin >> compCasilla;
            if (compCasilla == "si" || compCasilla == "SI" || compCasilla == "Si") {
                if (user.cash >= prop.precio) {
                    user = PerderDinero(user, prop.precio);
                    user.propiedades.push_back(prop);
                    std::cout << user.nombre << " a comprado la propiedad " << prop.nombre << "." << std::endl;
                }
                std::cout << user.nombre << " no tiene suficiente dinero y por ende se pasa a subastar." << std::endl;
            }
            // aqui va la subasta del servicio
        }
        else if (propProp != user.nombre) {
            std::cout << user.nombre << " a caido en " << prop.nombre << ". Casilla la cual es propiedad de " << propProp << std::endl;
            // falta lo del monopolio
        }
    }

    else if (cas.tipo == "ferrocarril") {
        Ferrocarril& ferro = partida.tablero.ferrocarriles[cas.indiceTipo];
        std::string propFerro = PropietarioDeFerrocarril(partida, ferro.nombre);
        // la casilla no tiene dueño
        if (propFerro == "except") {
            std::cout << user.nombre << " tiene " << user.cash << "$." << " Desea comprar la casilla " << ferro.nombre << " por el modico precio de " << ferro.valor << " ? (si o no)" << std::endl;
            std::string compCasilla;
            std::cin >> compCasilla;
            if (compCasilla == "si" || compCasilla == "SI" || compCasilla == "Si") {
                if (user.cash >= ferro.valor) {
                    user = PerderDinero(user, ferro.valor);
                    user.ferrocarriles.push_back(ferro);
                    std::cout << user.nombre << " a comprado el ferrocarril " << ferro.nombre << "." << std::endl;
                    return;
                }
                else {
                    std::cout << user.nombre << " no tiene suficiente dinero y por ende se pasa a subastar." << std::endl;
                }
            }
            // aqui va la subasta del ferrocarril
        }
        // la casilla tiene dueño
        else {
            std::cout << user.nombre << " a caido en " << ferro.nombre << ". Casilla la cual es propiedad de " << propFerro << std::endl;
            int precio = ValorRentaFerrocarril(NumeroDeFerrocarriles(partida, propFerro));
            partida.usuarios[propFerro] = GanarDinero(partida.usuarios[propFerro], precio);
            user = PerderDinero(user, precio);
            std::cout << user.nombre << " le ha pagado " << precio << " a " << propFerro << ". " << user.nombre << " le quedan " << user.cash << "$" << std::endl;

            // falta manejar lo de que el usuario pueda quedarse sin dinero o en negativo y por ende deba de subastar o hipotecar
        }
        
    }

    // falta esto
    else if (cas.tipo == "especial") {

    }
}