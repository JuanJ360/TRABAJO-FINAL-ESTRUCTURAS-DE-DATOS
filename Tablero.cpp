#include "Tablero.h"

Tablero CrearTablero() {
    std::ifstream archivoPropiedades("viernes13/Propiedades.json");
    if (!archivoPropiedades.is_open()) {
        throw std::runtime_error("CrearTablero: Error al abrir el archivo de propiedades");
    }
    json prop;
    archivoPropiedades >> prop;

    std::ifstream archivoFerrcarriles("viernes13/Ferrocarriles.json");
    if (!archivoFerrcarriles.is_open()) {
        throw std::runtime_error("CrearTablero: Error al abrir el archivo de ferrocarriles");
    }
    json ferro;
    archivoFerrcarriles >> ferro;

    std::ifstream archivoServicios("viernes13/Servicios.json");
    if (!archivoServicios.is_open()) {
        throw std::runtime_error("CrearTablero: Error al abrir el archivo de servicios");
    }
    json serv;
    archivoServicios >> serv;

    std::ifstream archivosCasillasEspeciales("viernes13/CasillasEspeciales.json");
    if (!archivosCasillasEspeciales.is_open()) {
        throw std::runtime_error("CrearTablero: Error al abrir el archivo de casillas especiales");
    }
    json casEsp;
    archivosCasillasEspeciales >> casEsp;

    std::ifstream archivosCasillas("viernes13/Casillas.json");
    if (!archivosCasillas.is_open()) {
        throw std::runtime_error("CrearTablero: Error al abrir el archivo de casillas");
    }
    json cas;
    archivosCasillas >> cas;

    int i, j;

    // crear propiedades
    std::vector<Propiedad> propiedades;
    for (i = 0; i < prop.size(); i++) {
        int tmp[6];
        for (j = 0; j < 6; j++) {
            tmp[j] = prop[i]["alquiler"][j];
        }
        propiedades.push_back(CrearPropiedad(prop[i]["nombre"], prop[i]["subTipo"], prop[i]["color"], prop[i]["hipotecada"], prop[i]["valor"], tmp));
    }

    // crear ferrocarriles
    std::vector<Ferrocarril> ferrocarriles;
    for (i = 0; i < ferro.size(); i++) {
        int tmp[4];
        for (j = 0; j < 4; j++) {
            tmp[j] = ferro[i]["alquiler"][j];
        }
        ferrocarriles.push_back(CrearFerrocarril(ferro[i]["nombre"], ferro[i]["valor"], ferro[i]["hipotecada"], tmp));
    }

    // crear servicios
    std::vector<Servicio> servicios;
    for (i = 0; i < serv.size(); i++) {
        servicios.push_back(CrearServicio(serv[i]["nombre"], serv[i]["valor"], serv[i]["hipoteca"]));
    }

    // crear casillas especailes
    std::vector<std::string> casillasEspeciales;
    for (i = 0; i < casEsp.size(); i++) {
        casillasEspeciales.push_back(casEsp[i]["nombre"]);
    }

    // enlazar todas las cartas con sus posiciones
    std::vector<Casilla> casillas;
    for (i = 0; i < cas.size(); i++) {
        casillas.push_back(CrearCasilla(cas[i]["tipo"], cas[i]["posicion"]));
    }

    Tablero tablero;
    tablero.casillas = casillas;
    tablero.especiales = casillasEspeciales;
    tablero.ferrocarriles = ferrocarriles;
    tablero.servicios = servicios;
    tablero.propiedades = propiedades;


    return tablero;
}