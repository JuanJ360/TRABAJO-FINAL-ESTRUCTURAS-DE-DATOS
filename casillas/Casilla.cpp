#include "Casilla.h"

Casilla CrearCasilla(std::string _tipo, int _indiceTipo) {
    Casilla c;
    c.tipo = _tipo;
    c:_indiceTipo = _indiceTipo;
    return c;
}