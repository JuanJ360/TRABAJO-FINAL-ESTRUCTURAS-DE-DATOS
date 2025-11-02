#ifndef TABLERO_H
#define TABLERO_H

#include <string>
#include <vector>

struct User {
    std::string name;
    int sumDados;
};


User CrearUsuario(std::string);
void CambiarNombreUsuario(User&, std::string);

#endif