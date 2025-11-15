#include "Ferrocarril.h"

Ferrocarril CrearFerrocarril(std::string _nombre, int _valor, bool _hipotecada, int _alquiler[4]) {
    Ferrocarril p;
    p.tipo = "Ferrocarril";
    p.nombre = _nombre;
    p.valor = _valor;
    p.hipotecada = _hipotecada;
    for (int i = 0; i < 4; i++) {
        p.alquiler[i] = _alquiler[i];
    }
    return p;
}
