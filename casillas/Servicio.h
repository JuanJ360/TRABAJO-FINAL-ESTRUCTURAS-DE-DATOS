#ifndef SERVICIO_H
#define SERVICIO_H

#include <string>

struct Servicio {
    std::string tipo;
    std::string nombre;
    int valor;
    int hipoteca;
};

// OPERACIONES
Servicio CrearServicio(std::string, int, int);

#endif