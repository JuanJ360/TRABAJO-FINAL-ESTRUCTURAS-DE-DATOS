#include "Propiedad.h"

Propiedad CrearPropiedad(std::string _nombre, std::string _subTipo, std::string _color, bool _hipotecada, int _precio, int _alquiler[6], int _valorCasa, int _valorHotel, int _valorHipotecar, int _valorDesHipotecar) {
    Propiedad p;
    p.tipo = "Propiedad";
    p.name = _nombre;
    p.subTipo = _subTipo;
    p.color = _color;
    p.precio = _precio;
    p.hipotecada = _hipotecada;
    for (int i = 0; i < 6; ++i) {
        p.alquiler[i] = _alquiler[i];
    }
    p.valorCasa = _valorCasa;
    p.valorHotel = _valorHotel;
    p.valorHipotecar = _valorHipotecar;
    p.valorDesHipotecar = _valorDesHipotecar;
    return p;
}