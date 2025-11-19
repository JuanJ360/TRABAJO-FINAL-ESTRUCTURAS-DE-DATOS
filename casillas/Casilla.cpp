#include "Casilla.h"

Casilla CrearCasilla(std::string _nombre, std::string _tipo, int _indiceTipo) {
    Casilla c;
    c.nombre = _nombre;
    c.tipo = _tipo;
    c.indiceTipo = _indiceTipo;
    return c;
}

