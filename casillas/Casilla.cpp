#include "Casilla.h"

Casilla CrearCasilla(std::string _tipo, int _indiceTipo) {
    Casilla c;
    c.tipo = _tipo;
    c.indiceTipo = _indiceTipo;
    return c;
}

