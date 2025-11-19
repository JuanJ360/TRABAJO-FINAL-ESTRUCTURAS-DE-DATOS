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

void AvanzarJugador(Partida& p, User& jugador) {

        // Verificar si está en la cárcel
    if (EstaArrestado(p.carcel, jugador.nombre)) {

        // Aplicar regla de 3 turnos
        ReglaTercerTurnoCarcel(p.carcel, jugador.nombre);

        // Si salió, continua el turno normal
        if (!EstaArrestado(p.carcel, jugador.nombre)) {
            std::cout << jugador.nombre << " ha quedado libre. Continúa su turno.\n";
        } else {
            std::cout << jugador.nombre << " sigue en la cárcel.\n";
            return;  // NO juega este turno
        }
    }


    std::cout << "\nTurno de " << jugador.nombre << ". Presiona ENTER para tirar los dados...";
    std::cin.get();

    int d1 = TirarDado();
    int d2 = TirarDado();
    int suma = d1 + d2;

    std::cout << " Dados: " << d1 << " + " << d2 << " = " << suma << "\n";

    //Contabilizar par
    if (d1 == d2)
        jugador.contPares++;
    else
        jugador.contPares = 0;

    //Llamar a la regla externa
    ReglaTercerParFuera(p.carcel, jugador);

    // Si quedó arrestado, no sigue el turno
    if (EstaArrestado(p.carcel, jugador.nombre)) {
        std::cout << jugador.nombre << " fue enviado a la cárcel.\n";
        return;
    }

    //  Mover al jugador
    int posicionAnterior = jugador.posicion;
    jugador.posicion = (posicionAnterior + suma) % 40;

    if (posicionAnterior + suma >= 40) {
        std::cout << ">>> " << jugador.nombre << " pasó por la salida y recibe $200.\n";
        jugador.cash += 200;
    }

    std::cout << jugador.nombre << " ahora está en la casilla " << jugador.posicion << ".\n";

    EjecutarCasilla(p,jugador,suma);

    //Si sacó par, vuelve a tirar
    if (d1 == d2)
        AvanzarJugador(p, jugador);
}

void ReglaTercerTurnoCarcel(Carcel& carcel, const std::string& nombre) {

    // Obtener referencia al par <User*, turnos>
    auto& data = carcel.prisioneros[nombre];
    User* user = data.first;
    int& turnos = data.second;

    // Incrementar turnos
    turnos++;

    std::cout << user->nombre << " lleva " << turnos << " turnos en la cárcel.\n";

    // Si ya cumplió 3 turnos debe ser liberado
    if (turnos >= 3) {
        std::cout << user->nombre << " ha cumplido 3 turnos en la cárcel. Queda libre.\n";

        LiberarDeLaCarcel(carcel, nombre);

        // Sale a la casilla 10
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

bool PropiedadEnMonopolio(Partida& partida, const std::string nomPropiedad) {

    // Buscar la propiedad en el tablero
    std::string colorBuscado;
    for (const auto& p : partida.tablero.propiedades) {
        if (p.nombre == nomPropiedad) {
            colorBuscado = p.color;
            break;
        }
    }

    if (colorBuscado.empty()) {
        // No existe esa propiedad en el tablero
        return false;
    }

    // Saber cuántas propiedades totales existen de ese color
    int totalColor = 0;
    for (const auto& p : partida.tablero.propiedades) {
        if (p.color == colorBuscado)
            totalColor++;
    }

    // Encontrar el jugador del turno actual
    std::string nombreJugador = partida.ordenUsuarios[ partida.nTurno ];
    User& jugador = partida.usuarios[nombreJugador];

    // Contar cuántas de ese color posee el jugador
    int poseeColor = 0;
    for (const auto& p : jugador.propiedades) {
        if (p.color == colorBuscado)
            poseeColor++;
    }

    // Condición de monopolio
    return poseeColor == totalColor;
}


// adicionalmente hay que incorporarle el tema de las subastas

void EjecutarCasilla(Partida& partida, User& user, int tiradaDeDados) {

    Casilla cas = ObtenerCasilla(partida.tablero, user.posicion);

    // ===================================================
    // SERVICIOS
    // ===================================================
    if (cas.tipo == "servicio") {

        Servicio& servi = partida.tablero.servicios[cas.indiceTipo];
        std::string propietario = PropietarioDeServicio(partida, servi.nombre);

        // SIN DUEÑO → comprar
        if (propietario == "except") {

            std::cout << user.nombre << " tiene " << user.cash
                      << "$. Desea comprar " << servi.nombre
                      << " por " << servi.valor << "? (si/no)\n";

            std::string r;
            std::cin >> r;

            if (r == "si" && user.cash >= servi.valor) {
                user = PerderDinero(user, servi.valor);
                user.servicios.push_back(servi);
                std::cout << user.nombre << " compró el servicio.\n";
                return;
            }

            std::cout << "No tiene dinero o no quiso comprar. → SUBASTA\n";
            // pendiente subasta
            return;
        }

        // CON DUEÑO Y NO ES EL MISMO
        if (propietario != user.nombre) {

            int renta = ValorRentaServicio(tiradaDeDados,
                                           NumeroDeServicios(partida, propietario));

            std::cout << user.nombre << " cayó en " << servi.nombre
                      << " de " << propietario << ". Debe pagar " << renta << "$.\n";

            user = PerderDinero(user, renta);
            partida.usuarios[propietario] =
                GanarDinero(partida.usuarios[propietario], renta);

            return;
        }
    }

    // ===================================================
    // PROPIEDADES
    // ===================================================
    else if (cas.tipo == "propiedad") {

        Propiedad& prop = partida.tablero.propiedades[cas.indiceTipo];

        // CORREGIDO: función correcta
        std::string propietario = PropietarioDePropiedad(partida, prop.nombre);

        // SIN DUEÑO
        if (propietario == "except") {

            std::cout << user.nombre << " tiene " << user.cash
                      << "$. Desea comprar " << prop.nombre
                      << " por " << prop.precio << "? (si/no)\n";

            std::string r;
            std::cin >> r;

            if (r == "si" && user.cash >= prop.precio) {
                user = PerderDinero(user, prop.precio);
                user.propiedades.push_back(prop);
                std::cout << user.nombre << " compró la propiedad.\n";
                return;
            }

            std::cout << "No tiene dinero o no quiso comprar. → SUBASTA\n";
            return;
        }

        // CON DUEÑO — hay que pagar renta
        if (propietario != user.nombre) {

            bool monopolio = PropiedadEnMonopolio(partida, prop.nombre);

            int renta = ValorRentaPropiedad(prop, monopolio);

            std::cout << user.nombre << " cayó en " << prop.nombre
                      << " de " << propietario << ". Debe pagar " << renta << "$.\n";

            user = PerderDinero(user, renta);
            partida.usuarios[propietario] =
                GanarDinero(partida.usuarios[propietario], renta);

            return;
        }
    }

    // ===================================================
    // FERROCARRILES
    // ===================================================
    else if (cas.tipo == "ferrocarril") {

        Ferrocarril& ferro = partida.tablero.ferrocarriles[cas.indiceTipo];
        std::string propietario = PropietarioDeFerrocarril(partida, ferro.nombre);

        // SIN DUEÑO
        if (propietario == "except") {

            std::cout << user.nombre << " tiene " << user.cash
                      << "$. Desea comprar " << ferro.nombre
                      << " por " << ferro.valor << "? (si/no)\n";

            std::string r;
            std::cin >> r;

            if (r == "si" && user.cash >= ferro.valor) {
                user = PerderDinero(user, ferro.valor);
                user.ferrocarriles.push_back(ferro);
                std::cout << user.nombre << " compró el ferrocarril.\n";
                return;
            }

            std::cout << "No tiene dinero o no quiso comprar. → SUBASTA\n";
            return;
        }

        // CON DUEÑO
        if (propietario != user.nombre) {

            int renta = ValorRentaFerrocarril(
                NumeroDeFerrocarriles(partida, propietario));

            std::cout << user.nombre << " cayó en " << ferro.nombre
                      << " de " << propietario << ". Debe pagar " << renta << "$.\n";

            user = PerderDinero(user, renta);
            partida.usuarios[propietario] =
                GanarDinero(partida.usuarios[propietario], renta);

            return;
        }
    }

    // ===================================================
    // ESPECIALES (Carcel, Suerte, Parking, Ir a la cárcel)
    // ===================================================
    else if (cas.tipo == "especial") {
        // aquí metemos lo que quieras: ir a cárcel, suerte, impuestos, etc.
    }
}
