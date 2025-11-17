#include "Banco.h"

Banco crearBanco(std::vector<Propiedad> _propiedades) {
    Banco b;
    b.propiedades = _propiedades;
    return b;
}