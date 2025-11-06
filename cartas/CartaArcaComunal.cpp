#include "CartaArcaComunal.h"

CartaArcaComunal CrearCartaArcaComunal(std::string _tipo, std::string _nombre, std::string _mensaje) {
    CartaArcaComunal cac;
    cac.tipo = _tipo;
    cac.nombre = _nombre;
    cac.mensaje = _mensaje;
    return cac;
}