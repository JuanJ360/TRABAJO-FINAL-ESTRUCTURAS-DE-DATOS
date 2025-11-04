#include "User.h"

// implementación de User.h

User CrearUsuario(std::string _name) {
    User user;
    user.name = _name;
    user.cash = 0; // se inicializa el dinero del usuario en 0
    user.sumDados = 0; // se inicializa la suma de los tiros de los dados del usuario en 0
    user.activo = true;
    return user;
}

User CambiarNombreUsuario(User user, std::string newName) {
    user.name = newName;
    return user;
}

User AumentarSumSados(User user, int aumento) {
    user.sumDados += aumento;
    return user;
}

User GanarDinero(User user, int dinero) {
    user.cash += dinero;
    return user;
}

// creo que es mejor manejar el tema de las deudas y bancarrotas fuera de el usuario asi que esta implementación sera mas corta
User PerderDinero(User user, int dinero) {
    user.cash -= dinero;
    return user;
}

User UsuarioEliminado(User user) {
    user.activo = false;
    return user;
}