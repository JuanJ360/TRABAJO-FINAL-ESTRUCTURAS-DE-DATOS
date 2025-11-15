#include "Propiedad.h"

Propiedad CrearPropiedad(std::string _nombre, std::string _subTipo, std::string _color, bool _hipotecada, int _valor, int _alquiler[6]) {
    Propiedad p;
    p.tipo = "Propiedad";
    p.name = _nombre;
    p.subTipo = _subTipo;
    p.color = _color;
    p.valor = _valor;
    p.hipotecada = _hipotecada;
    for (int i = 0; i < 6; ++i) {
        p.alquiler[i] = _alquiler[i];
    }
    return p;
}