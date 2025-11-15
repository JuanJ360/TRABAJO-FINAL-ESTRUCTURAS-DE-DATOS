#include "Servicio.h"

Servicio CrearServicio (std::string _nombre, int _valor, int _hipoteca){
    Servicio s;
    s.nombre = _nombre;
    s.valor = _valor;
    s.hipoteca = _hipoteca;
    s.tipo = "Servicio";
    return s;
}