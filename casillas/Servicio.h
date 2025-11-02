#ifndef SERVICIO_H
#define SERVICIO_H

#include <string>

struct Servicio {
    std::string type;
    std::string name;
    int value;
};

// OPERACIONES
Servicio CrearServicio(std::string);

#endif