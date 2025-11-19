#include "Propiedad.h"

Propiedad CrearPropiedad(std::string _nombre, std::string _subTipo, std::string _color, bool _hipotecada, int _precio, int _alquiler[6], int _valorCasa, int _valorHotel, int _valorHipotecar, int _valorDesHipotecar) {
    Propiedad p;
    p.tipo = "Propiedad";
    p.nombre = _nombre;
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
    p.numCasas = 0;
    p.numHoteles = 0;
    return p;
}

Propiedad ConstruirNCasas(Propiedad prop, int casas) {
    if (prop.numCasas + casas > 4) {
        throw std::invalid_argument("Propiedad: ConstruirNCasas: El total de casas en una propiedad no puede superar las 4");
    }
    if (prop.numHoteles == 1) {
        throw std::invalid_argument("Propiedad: ConstruirNCasas: No se pueden consturir casas en una propiedad que ya posee un hotel.");
    }
    prop.numCasas += casas;
    return prop;
}

Propiedad ConsturirHotel(Propiedad prop) {
    if (prop.numCasas != 4) {
        throw std::invalid_argument("Propiedad: ConsturirHotel: Para construir un hotel en una propiedad es necesario tener 4 casas en dicha propiedad.");
    }
    prop.numCasas = 0;
    prop.numHoteles = 1;
    return prop;
}

int ValorRentaPropiedad(Propiedad& prop, bool monopolio) {
    
    if (!monopolio) {
        return prop.alquiler[0];
    }
    else {
        // no hay casas
        if (prop.numCasas == 0 && prop.numHoteles == 0) {
            return 2 * prop.alquiler[0];
        }
        // hay n casas pero no hay un hotel
        if (prop.numCasas > 0 && prop.numHoteles == 0) {
            return prop.alquiler[prop.numCasas];
        }
        // hay un hotel
        if (prop.numHoteles == 1) {
            return prop.alquiler[5];
        }
    }

    return 0;
}