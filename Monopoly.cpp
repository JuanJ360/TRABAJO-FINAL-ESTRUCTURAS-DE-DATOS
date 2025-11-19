// Monopoly.cpp
#include "Monopoly.h"
#include <iostream>
#include <algorithm>
#include <cctype>

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
        std::cout << "7. Gestionar propiedades del jugador actual\n";
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

            case 7:
                MenuPropiedades();
                break;

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

// --- HELPERS ---

std::vector<Propiedad*> Monopoly::ObtenerPropsColor(Partida& p, const std::string& color, const std::string& jugador) {
    std::vector<Propiedad*> res;
    auto it = p.usuarios.find(jugador);
    if (it == p.usuarios.end()) return res;
    User& u = it->second;
    for (auto &prop : u.propiedades) {
        if (prop.color == color) res.push_back(&prop);
    }
    return res;
}

bool Monopoly::TieneMonopolio(Partida& p, const std::string& jugador, const std::string& color) {
    int totalColor = 0;
    for (const auto &prop : p.tablero.propiedades)
        if (prop.color == color) totalColor++;

    int tiene = 0;
    auto it = p.usuarios.find(jugador);
    if (it == p.usuarios.end()) return false;
    for (const auto &prop : it->second.propiedades)
        if (prop.color == color) tiene++;

    return (totalColor > 0) && (tiene == totalColor);
}

bool Monopoly::PuedeConstruirCasa(Partida& p, const std::string& jugador, Propiedad& prop) {
    if (prop.hipotecada) return false;
    if (prop.numHoteles == 1) return false;
    if (!TieneMonopolio(p, jugador, prop.color)) return false;

    auto props = ObtenerPropsColor(p, prop.color, jugador);
    // Regla: no puede haber una propiedad con más de 1 casa menos que otra (equilibrio)
    for (auto* other : props) {
        if (prop.numCasas > other->numCasas) return false; // no elevar sin equilibrio
    }
    if (prop.numCasas >= 4) return false; // máximo 4 antes de hotel
    return true;
}

bool Monopoly::PuedeConstruirHotel(Partida& p, const std::string& jugador, Propiedad& prop) {
    if (prop.hipotecada) return false;
    if (!TieneMonopolio(p, jugador, prop.color)) return false;
    if (prop.numCasas != 4) return false;
    if (prop.numHoteles == 1) return false;

    // Todas las propiedades del color deben tener 4 casas
    auto props = ObtenerPropsColor(p, prop.color, jugador);
    for (auto* other : props)
        if (other->numCasas != 4) return false;

    return true;
}

// --- MOSTRAR PROPIEDADES ---

void Monopoly::MostrarPropiedadesJugador(const std::string& jugador) {
    if (!juegoIniciado) { std::cout << "No hay partida iniciada.\n"; return; }
    auto it = partidaActual.usuarios.find(jugador);
    if (it == partidaActual.usuarios.end()) { std::cout << "Jugador no encontrado.\n"; return; }

    const User& u = it->second;
    std::cout << "\nPROPIEDADES DE " << jugador << ":\n";
    if (u.propiedades.empty()) {
        std::cout << "  Ninguna.\n";
        return;
    }
    for (const auto& p : u.propiedades) {
        std::cout << "- " << p.nombre
                  << " | Color: " << p.color
                  << " | Casas: " << p.numCasas
                  << " | Hotel: " << p.numHoteles
                  << " | Hipotecada: " << (p.hipotecada ? "Sí" : "No")
                  << " | Precio casa: " << p.valorCasa
                  << " | Precio hotel: " << p.valorHotel
                  << "\n";
    }
}

// --- OPERACIONES ---

bool Monopoly::ComprarCasa(const std::string& jugador, const std::string& nombreProp) {
    if (!juegoIniciado) { std::cout<<"No hay partida iniciada.\n"; return false; }
    // Guardar estado para permitir deshacer
    GuardarEstadoPartida();

    User& u = partidaActual.usuarios[jugador];
    for (auto& p : u.propiedades) {
        if (p.nombre == nombreProp) {
            if (!PuedeConstruirCasa(partidaActual, jugador, p)) {
                std::cout << "No se puede construir una casa en " << nombreProp << ".\n";
                return false;
            }
            if (u.cash < p.valorCasa) {
                std::cout << "No tienes suficiente dinero.\n";
                return false;
            }
            u.cash -= p.valorCasa;
            p.numCasas++;
            std::cout << "Casa construida en " << p.nombre << ". Casas totales: " << p.numCasas << "\n";
            return true;
        }
    }
    std::cout << "Propiedad no encontrada.\n";
    return false;
}

bool Monopoly::ComprarHotel(const std::string& jugador, const std::string& nombreProp) {
    if (!juegoIniciado) { std::cout<<"No hay partida iniciada.\n"; return false; }
    GuardarEstadoPartida();

    User& u = partidaActual.usuarios[jugador];
    for (auto& p : u.propiedades) {
        if (p.nombre == nombreProp) {
            if (!PuedeConstruirHotel(partidaActual, jugador, p)) {
                std::cout << "No se puede construir hotel en " << nombreProp << ".\n";
                return false;
            }
            if (u.cash < p.valorHotel) {
                std::cout << "No tienes suficiente dinero.\n";
                return false;
            }
            u.cash -= p.valorHotel;
            p.numCasas = 0;
            p.numHoteles = 1;
            std::cout << "Hotel construido en " << p.nombre << ".\n";
            return true;
        }
    }
    std::cout << "Propiedad no encontrada.\n";
    return false;
}

bool Monopoly::VenderCasa(const std::string& jugador, const std::string& nombreProp) {
    if (!juegoIniciado) { std::cout<<"No hay partida iniciada.\n"; return false; }
    GuardarEstadoPartida();

    User& u = partidaActual.usuarios[jugador];
    for (auto& p : u.propiedades) {
        if (p.nombre == nombreProp) {
            if (p.numCasas == 0) { std::cout << "No hay casas para vender.\n"; return false; }
            // regla equilibrio: no vender si dejaría desigualdad
            auto props = ObtenerPropsColor(partidaActual, p.color, jugador);
            for (auto* other : props) {
                if (p.numCasas < other->numCasas) {
                    std::cout << "No se puede vender casa: rompería equilibrio.\n";
                    return false;
                }
            }
            p.numCasas--;
            u.cash += p.valorCasa / 2;
            std::cout << "Casa vendida. Casas actuales: " << p.numCasas << "\n";
            return true;
        }
    }
    std::cout << "Propiedad no encontrada.\n";
    return false;
}

bool Monopoly::VenderHotel(const std::string& jugador, const std::string& nombreProp) {
    if (!juegoIniciado) { std::cout<<"No hay partida iniciada.\n"; return false; }
    GuardarEstadoPartida();

    User& u = partidaActual.usuarios[jugador];
    for (auto& p : u.propiedades) {
        if (p.nombre == nombreProp) {
            if (p.numHoteles == 0) { std::cout << "No hay hotel para vender.\n"; return false; }
            p.numHoteles = 0;
            p.numCasas = 4; // vender hotel deja 4 casas
            u.cash += p.valorHotel / 2;
            std::cout << "Hotel vendido. La propiedad tiene ahora 4 casas.\n";
            return true;
        }
    }
    std::cout << "Propiedad no encontrada.\n";
    return false;
}

bool Monopoly::HipotecarPropiedad(const std::string& jugador, const std::string& nombreProp) {
    if (!juegoIniciado) { std::cout<<"No hay partida iniciada.\n"; return false; }
    GuardarEstadoPartida();

    User& u = partidaActual.usuarios[jugador];
    for (auto& p : u.propiedades) {
        if (p.nombre == nombreProp) {
            if (p.hipotecada) { std::cout << "Ya está hipotecada.\n"; return false; }
            if (p.numCasas > 0 || p.numHoteles > 0) { std::cout << "Quita casas / hotel antes de hipotecar.\n"; return false; }
            p.hipotecada = true;
            u.cash += p.valorHipotecar;
            std::cout << "Propiedad hipotecada por $" << p.valorHipotecar << ".\n";
            return true;
        }
    }
    std::cout << "Propiedad no encontrada.\n";
    return false;
}

bool Monopoly::DeshipotecarPropiedad(const std::string& jugador, const std::string& nombreProp) {
    if (!juegoIniciado) { std::cout<<"No hay partida iniciada.\n"; return false; }
    GuardarEstadoPartida();

    User& u = partidaActual.usuarios[jugador];
    for (auto& p : u.propiedades) {
        if (p.nombre == nombreProp) {
            if (!p.hipotecada) { std::cout << "No está hipotecada.\n"; return false; }
            int costo = p.valorDesHipotecar;
            if (u.cash < costo) { std::cout << "No tienes suficiente dinero para deshipotecar.\n"; return false; }
            u.cash -= costo;
            p.hipotecada = false;
            std::cout << "Propiedad deshipotecada por $" << costo << ".\n";
            return true;
        }
    }
    std::cout << "Propiedad no encontrada.\n";
    return false;
}

void Monopoly::MenuPropiedades() {
    if (!juegoIniciado) { 
        std::cout << "No hay partida iniciada.\n"; 
        return; 
    }

    std::string jugadorActual = partidaActual.ordenUsuarios[partidaActual.nTurno];
    int opcion = -1;
    std::string nombre;

    while (true) {

        std::cout << "\n====== MENU DE PROPIEDADES (" << jugadorActual << ") ======\n";
        std::cout << "1. Ver propiedades\n";
        std::cout << "2. Construir casa\n";
        std::cout << "3. Construir hotel\n";
        std::cout << "4. Vender casa\n";
        std::cout << "5. Vender hotel\n";
        std::cout << "6. Hipotecar propiedad\n";
        std::cout << "7. Deshipotecar propiedad\n";
        std::cout << "0. Salir\n";
        std::cout << "Selecciona una opcion: ";

        std::cin >> opcion;
        std::cin.ignore(); // ← elimina solo el salto de línea sobrante

        if (opcion == 0) {
            std::cout << "Saliendo del menu de propiedades.\n";
            break;  // ← sale del while sin do-while
        }

        switch (opcion) {
            case 1:
                MostrarPropiedadesJugador(jugadorActual);
                break;

            case 2:
                std::cout << "Nombre de la propiedad para construir casa: ";
                getline(std::cin, nombre);
                ComprarCasa(jugadorActual, nombre);
                break;

            case 3:
                std::cout << "Nombre de la propiedad para construir hotel: ";
                getline(std::cin, nombre);
                ComprarHotel(jugadorActual, nombre);
                break;

            case 4:
                std::cout << "Nombre de la propiedad para vender una casa: ";
                getline(std::cin, nombre);
                VenderCasa(jugadorActual, nombre);
                break;

            case 5:
                std::cout << "Nombre de la propiedad para vender el hotel: ";
                getline(std::cin, nombre);
                VenderHotel(jugadorActual, nombre);
                break;

            case 6:
                std::cout << "Nombre de la propiedad a hipotecar: ";
                getline(std::cin, nombre);
                HipotecarPropiedad(jugadorActual, nombre);
                break;

            case 7:
                std::cout << "Nombre de la propiedad a deshipotecar: ";
                getline(std::cin, nombre);
                DeshipotecarPropiedad(jugadorActual, nombre);
                break;

            default:
                std::cout << "Opcion invalida.\n";
        }
    }
}