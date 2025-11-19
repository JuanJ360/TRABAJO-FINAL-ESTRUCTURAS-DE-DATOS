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
    p.arcaComunal = IniciarArcaComunal();
    p.suerte = IniciarSuerte();


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


// Función auxiliar para validar si un jugador tiene suficiente dinero
bool PuedeComprar(const User& user, int precio) {
    return user.cash >= precio;
}

// Función auxiliar para normalizar entrada del usuario
std::string NormalizarRespuesta(std::string entrada) {
    std::transform(entrada.begin(), entrada.end(), entrada.begin(), ::tolower);
    return entrada;
}

void EjecutarCasilla(Partida& partida, User& user, int tiradaDeDados) {

    Casilla cas = ObtenerCasilla(partida.tablero, user.posicion);

    // Servicios
    if (cas.tipo == "servicio") {

        Servicio& servi = partida.tablero.servicios[cas.indiceTipo];
        std::string propietario = PropietarioDeServicio(partida, servi.nombre);

        // sin dueño para comprar
        if (propietario == "except") {

            std::cout << user.nombre << " tiene " << user.cash << "$. Desea comprar " << servi.nombre << " por " << servi.valor << "? (si/no)\n";

            std::string r;
            std::cin >> r;
            r = NormalizarRespuesta(r);

            if (r == "si" && PuedeComprar(user, servi.valor)) {
                user = PerderDinero(user, servi.valor);
                user.servicios.push_back(servi);
                std::cout << user.nombre << " compró el servicio.\n";
                partida.usuarios[user.nombre] = user;
                return;
            }

            std::cout << "No tiene dinero o no quiso comprar. → SUBASTA\n";
            SubastarPropiedad(partida, user, cas.nombre, false);
            return;
        }

        // CON DUEÑO Y NO ES EL MISMO
        if (propietario != user.nombre) {

            int renta = ValorRentaServicio(tiradaDeDados, NumeroDeServicios(partida, propietario));

            std::cout << user.nombre << " cayó en " << servi.nombre << " de " << propietario << ". Debe pagar " << renta << "$.\n";

            user = PerderDinero(user, renta);
            partida.usuarios[propietario] = GanarDinero(partida.usuarios[propietario], renta);
            partida.usuarios[user.nombre] = user;

            return;
        }
    }

    // PROPIEDADES
    else if (cas.tipo == "propiedad") {

        Propiedad& prop = partida.tablero.propiedades[cas.indiceTipo];
        std::string propietario = PropietarioDePropiedad(partida, prop.nombre);

        // SIN DUEÑO
        if (propietario == "except") {

            std::cout << user.nombre << " tiene " << user.cash << "$. Desea comprar " << prop.nombre << " por " << prop.precio << "? (si/no)\n";

            std::string r;
            std::cin >> r;
            r = NormalizarRespuesta(r);

            if (r == "si" && PuedeComprar(user, prop.precio)) {
                user = PerderDinero(user, prop.precio);
                user.propiedades.push_back(prop);
                std::cout << user.nombre << " compró la propiedad.\n";
                partida.usuarios[user.nombre] = user;
                return;
            }

            std::cout << "No tiene dinero o no quiso comprar. → SUBASTA\n";
            SubastarPropiedad(partida, user, cas.nombre, false);
            return;
        }

        // con dueño entonces hay que pagar renta
        if (propietario != user.nombre) {

            bool monopolio = PropiedadEnMonopolio(partida, prop.nombre);

            int renta = ValorRentaPropiedad(prop, monopolio);

            std::cout << user.nombre << " cayó en " << prop.nombre << " de " << propietario << ". Debe pagar " << renta << "$.\n";

            user = PerderDinero(user, renta);
            partida.usuarios[propietario] = GanarDinero(partida.usuarios[propietario], renta);
            partida.usuarios[user.nombre] = user;

            return;
        }
    }

    // FERROCARRILES
    else if (cas.tipo == "ferrocarril") {

        Ferrocarril& ferro = partida.tablero.ferrocarriles[cas.indiceTipo];
        std::string propietario = PropietarioDeFerrocarril(partida, ferro.nombre);

        // SIN DUEÑO
        if (propietario == "except") {

            std::cout << user.nombre << " tiene " << user.cash << "$. Desea comprar " << ferro.nombre << " por " << ferro.valor << "? (si/no)\n";

            std::string r;
            std::cin >> r;
            r = NormalizarRespuesta(r);

            if (r == "si" && PuedeComprar(user, ferro.valor)) {
                user = PerderDinero(user, ferro.valor);
                user.ferrocarriles.push_back(ferro);
                std::cout << user.nombre << " compró el ferrocarril.\n";
                partida.usuarios[user.nombre] = user;
                return;
            }

            std::cout << "No tiene dinero o no quiso comprar. → SUBASTA\n";
            SubastarPropiedad(partida, user, cas.nombre, false);
            return;
        }

        // CON DUEÑO
        if (propietario != user.nombre) {

            int renta = ValorRentaFerrocarril(NumeroDeFerrocarriles(partida, propietario));

            std::cout << user.nombre << " cayó en " << ferro.nombre
                      << " de " << propietario << ". Debe pagar " << renta << "$.\n";

            user = PerderDinero(user, renta);
            partida.usuarios[propietario] = GanarDinero(partida.usuarios[propietario], renta);
            partida.usuarios[user.nombre] = user;

            return;
        }
    }

    // ESPECIALES (Carcel, Suerte, Parking, Ir a la cárcel)
    else if (cas.tipo == "especial") {
        EjecutarCasillaEspecial(partida, user, cas.nombre);
    }
}

void SubastarPropiedad(Partida& partida, User& user, std::string nomCasilla, bool estaVendiendo) {
    std::cout << "\n=== SUBASTA DE " << nomCasilla << " ===" << std::endl;
    std::cout << "Los jugadores a participar de la subasta son:";
    
    std::vector<std::string> jugadoresSubasta;
    for (auto& uName: partida.ordenUsuarios) {
        if (uName != user.nombre) {
            jugadoresSubasta.push_back(uName);
            std::cout << " " << uName;
        }
    }
    std::cout << ".\n" << std::endl;

    // Si solo hay un jugador, él gana automáticamente por $1
    if (jugadoresSubasta.size() == 1) {
        std::cout << "Solo participa " << jugadoresSubasta[0] << ". Gana la subasta por $1.\n" << std::endl;
        AsignarPropiedad(partida, jugadoresSubasta[0], nomCasilla, 1);
        return;
    }
    
    std::string mejorPostor;
    int mejorPuesta = 0;
    
    std::string subastor;
    bool primeraRonda = true;
    
    while (true) {
        std::cout << "Ingrese el nombre del jugador que desea postar (o 'pasar' para retirarse): ";
        std::cin >> subastor;
        subastor = NormalizarRespuesta(subastor);

        if (subastor == "pasar") {
            if (mejorPostor.empty()) {
                std::cout << "Debe haber al menos un postor. Intente de nuevo.\n";
                continue;
            }
            break;
        }

        // Validar si el subastor está en la lista
        bool esValido = false;
        for (auto& jugador : jugadoresSubasta) {
            if (jugador == subastor) {
                esValido = true;
                break;
            }
        }

        if (!esValido) {
            std::cout << "El jugador debe estar en la lista de participantes.\n";
            continue;
        }

        std::cout << "Ingrese el precio que desea postar: $";
        int precio;
        std::cin >> precio;

        if (precio <= mejorPuesta) {
            std::cout << "La mejor puesta está en $" << mejorPuesta << " por " << mejorPostor 
                      << ". Debe postar más de eso.\n";
            continue;
        }

        mejorPostor = subastor;
        mejorPuesta = precio;
        std::cout << "Nueva mejor puesta: $" << mejorPuesta << " por " << mejorPostor << "\n\n";
        primeraRonda = false;
    }

    if (!mejorPostor.empty()) {
        AsignarPropiedad(partida, mejorPostor, nomCasilla, mejorPuesta);
        
        std::cout << "\n=== LA SUBASTA HA CULMINADO ===" << std::endl;
        std::cout << "Ganador: " << mejorPostor << std::endl;
        std::cout << "Precio final: $" << mejorPuesta << std::endl;
        std::cout << "Propiedad: " << nomCasilla << "\n" << std::endl;

        if (estaVendiendo) {
            std::cout << user.nombre << " ha vendido la propiedad y recibe $" << mejorPuesta << ".\n" << std::endl;
        }
    }
}

void AsignarPropiedad(Partida& partida, const std::string& comprador, const std::string& nomCasilla, int precio) {
    for (auto& c: partida.tablero.casillas) {
        if (c.nombre == nomCasilla) {

            if (c.tipo == "propiedad") {
                partida.usuarios[comprador].propiedades.push_back(partida.tablero.propiedades[c.indiceTipo]);
                partida.tablero.propiedades[c.indiceTipo].hipotecada = false;
            }
            else if (c.tipo == "ferrocarril") {
                partida.usuarios[comprador].ferrocarriles.push_back(partida.tablero.ferrocarriles[c.indiceTipo]);
                partida.tablero.ferrocarriles[c.indiceTipo].hipotecada = false;
            }
            else if (c.tipo == "servicio") {
                partida.usuarios[comprador].servicios.push_back(partida.tablero.servicios[c.indiceTipo]);
                partida.tablero.servicios[c.indiceTipo].hipoteca = false;
            }

            partida.usuarios[comprador] = PerderDinero(partida.usuarios[comprador], precio);
            break;
        }
    }
}

void EjecutarCasillaEspecial(Partida& partida, User& user, const std::string& nombre) {

    if (nombre == "Salida") {
        std::cout << user.nombre << " está en SALIDA.\n";
        return;
    }

    if (nombre == "Caja de Comunidad") {
        EjecutarArcaComunal(partida, user);
        return;
    }

    if (nombre == "Casilla de la Suerte") {
        EjecutarCartaSuerte(partida,user);
        return;
}

    if (nombre == "Impuesto sobre la Renta") {
        std::cout << user.nombre << " paga Impuesto sobre la renta ($200).\n";
        user.cash -= 200;
        return;
    }

    if (nombre == "Impuesto de Lujo") {
        std::cout << user.nombre << " paga Impuesto de Lujo ($75).\n";
        user.cash -= 75;
        return;
    }

    if (nombre == "Cárcel") {
        std::cout << user.nombre << " está VISITANDO la cárcel.\n";
        return;
    }

    if (nombre == "Ir a la Cárcel") {
        std::cout << user.nombre << " va DIRECTAMENTE a la CÁRCEL.\n";
        user.posicion = 10; 
        Arrestar(partida.carcel, &user);
        return;
    }

    if (nombre == "Estacionamiento Gratuito") {
        std::cout << user.nombre << " está en ESTACIONAMIENTO GRATUITO.\n";
        return;
    }

    std::cout << "Casilla especial no reconocida: " << nombre << "\n";
}

void EjecutarArcaComunal(Partida& p, User& user) {

    CartaArcaComunal carta = SacarCartaArcaComunal(p.arcaComunal);

    std::cout << user.nombre << " sacó una carta de CAJA DE COMUNIDAD:\n";
    std::cout << " -> " << carta.mensaje << "\n";


    if (carta.tipo == "Ganancia") {
        // Buscar número al final del mensaje
        int valor = std::stoi(carta.mensaje.substr(carta.mensaje.find("$") + 1));
        user.cash += valor;
        std::cout << user.nombre << " recibe $" << valor << ".\n";
        return;
    }

    if (carta.tipo == "Gasto") {
        int valor = std::stoi(carta.mensaje.substr(carta.mensaje.find("$") + 1));
        user.cash -= valor;
        std::cout << user.nombre << " paga $" << valor << ".\n";
        return;
    }

    if (carta.tipo == "Movimiento") {

        // Adelántese a salida
        if (carta.nombre == "Adelántese a la Salida") {
            user.posicion = 0;
            user.cash += 200;
            std::cout << user.nombre << " avanza a SALIDA y cobra $200.\n";
            return;
        }

        // Ir a la cárcel
        if (carta.nombre == "Ir a la Cárcel") {
            std::cout << user.nombre << " va DIRECTAMENTE a la CÁRCEL.\n";
            user.posicion = 10;
            Arrestar(p.carcel, &user);
            return;
        }
    }

    if (carta.tipo == "Especial") {

        if (carta.nombre == "Salga Gratis de la Cárcel") {
            user.cartaSalirDeLaCarcel = true;
            std::cout << user.nombre << " guarda una carta de 'Salir Gratis de la Cárcel'.\n";
            return;
        }
    }

    // Ganancias para todos los jugadores 
    if (carta.tipo == "Gasto (Gral)") {

        // Se extrae el número desde el mensaje
        int valor = std::stoi(carta.mensaje.substr(carta.mensaje.find("$") + 1));

        user.cash -= valor;

        std::cout << user.nombre << " paga $" << valor << " por reparaciones en la calle.\n";

        return;
    }


    std::cout << "(Carta no implementada, tipo desconocido: " << carta.tipo << ")\n";
}

void EjecutarCartaSuerte(Partida& p, User& user) 
{
    CartaSuerte carta = SacarCartaSuerte(p.suerte);

    std::cout << "\n[SUERTE] " << carta.mensaje << "\n";

    // ======= COBRAR =======
    if (carta.tipo == "cobrar") {

        if (carta.nombre == "avanza a la salida") {
            user.posicion = 0;
            user.cash += 200;
        }
        else if (carta.nombre == "dividendo bancario") {
            user.cash += 50;
        }
        else if (carta.nombre == "préstamo y edificio") {
            user.cash += 150;
        }
    }

    // ======= MOVIMIENTO =======
    else if (carta.tipo == "movimiento") {

        int posVieja = user.posicion;

        if (carta.nombre == "avanza a illinois") {
            user.posicion = 24; // Illinois Avenue
        }
        else if (carta.nombre == "avanza a st charles") {
            user.posicion = 11; // St. Charles
        }
        else if (carta.nombre == "avanza a paseo marítimo") {
            user.posicion = 39; // Boardwalk
        }
        else if (carta.nombre == "viaje a reading") {
            user.posicion = 5; // Reading Railroad
        }
        else if (carta.nombre == "retrocede 3") {
            user.posicion = (user.posicion - 3 + 40) % 40;
        }

        if (user.posicion < posVieja)
            user.cash += 200; // pasó por salida
    }

    // ======= MOVIMIENTO ESPECIAL =======
    else if (carta.tipo == "movimiento especial") {

        if (carta.nombre == "ferrocarril cercano 1" ||
            carta.nombre == "ferrocarril cercano 2")
        {
            // simplemente avanza al siguiente ferrocarril
            int posicion = user.posicion;

            if (posicion < 5) user.posicion = 5;
            else if (posicion < 15) user.posicion = 15;
            else if (posicion < 25) user.posicion = 25;
            else if (posicion < 35) user.posicion = 35;
            else {
                // pasó por salida
                user.posicion = 5;
                user.cash += 200;
            }
        }

        else if (carta.nombre == "utilidad cercana") {
            int pos = user.posicion;

            if (pos < 12) user.posicion = 12;
            else if (pos < 28) user.posicion = 28;
            else {
                user.posicion = 12;
                user.cash += 200;
            }
        }
    }

    // ======= PAGAR A JUGADORES =======
    else if (carta.tipo == "pagar a jugadores") {

        if (carta.nombre == "presidente del consejo") {
            for (auto& par : p.usuarios) {
                User& u = par.second;

                // saltar al jugador que sacó la carta
                if (u.nombre == user.nombre) 
                    continue;

                // cobra 50 del jugador actual
                user.cash -= 50;
                u.cash += 50;
            }

            std::cout << user.nombre << " paga $50 a cada jugador.\n";
        }
    }

    // ======= PAGAR AL BANCO =======
    else if (carta.tipo == "pagar al banco") {

        if (carta.nombre == "impuestos a los pobres")
            user.cash -= 15;
    }

    // ======= REPARACIONES  =======
    else if (carta.tipo == "reparaciones") {

        // versión compatible: 
        std::cout << "(Se ignoran reparaciones porque no tienes casas/hoteles)\n";
    }

    // ======= IR A LA CARCEL =======
    else if (carta.tipo == "cárcel") {

        user.posicion = 10;
        std::cout << user.nombre << " fue enviado a la cárcel.\n";
    }

    // ======= SALIR DE LA CARCEL =======
    else if (carta.tipo == "especial") {

        if (carta.nombre == "sal de la cárcel gratis") {
            user.cartaSalirDeLaCarcel = true;
        }
    }
}
