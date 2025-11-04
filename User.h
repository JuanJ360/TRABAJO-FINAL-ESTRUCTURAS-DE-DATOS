#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

struct User {
    std::string name;
    int cash;
    int sumDados;
    bool activo; // representa si el jugador puede seguir jugando o ya ha perdido
};


User CrearUsuario(std::string);
User CambiarNombreUsuario(User, std::string);
User AumentarSumSados(User, int);
User GanarDinero(User, int);
User PerderDinero(User, int);
User UsuarioEliminado(User);

#endif