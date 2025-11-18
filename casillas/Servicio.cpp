#include "Servicio.h"

Servicio CrearServicio (std::string _nombre, int _valor, int _hipoteca){
    Servicio s;
    s.nombre = _nombre;
    s.valor = _valor;
    s.hipoteca = _hipoteca;
    s.tipo = "Servicio";
    return s;
}

int ValorRentaServicio(int tirada, int nServicios) {
    if (nServicios == 1) {
        return 4 * tirada;
    }
    if (nServicios == 2) {
        return 10 * tirada;
    }
}

int MultDadoServicio(int ns) {
    if (ns == 0) {
        return 1;
    }
    if (ns == 1) {
        return 4;
    }
    if (ns == 2) {
        return 10;
    }
    else {
        throw std::invalid_argument("Servicio: MultiplicadorDadoServicio: El numero de servicios debe ser un numero no entre 0 y 2 ");
    }
}