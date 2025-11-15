#include "User.h"

// implementación de User.h

User CrearUsuario(std::string _name) {
    User user;
    user.name = _name;
    user.cash = 0; // se inicializa el dinero del usuario en 0
    user.posicion = 0; // se inicializa la suma de los tiros de los dados del usuario en 0
    user.contPares = 0;
    user.activo = true;
    user.cartaSalirDeLaCarcel = false;
    return user;
}

User CambiarNombreUsuario(User user, std::string newName) {
    user.name = newName;
    return user;
}

User AumentarPosicion(User user, int aumento) {
    user.posicion += aumento;
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

User ResetContPares(User user) {
    user.contPares = 0;
    return user;
}

User AumentarContPares(User user) {
    user.contPares++;
    return user;
}

User GanarCartaSalirDeLaCarcel(User user) {
    if (!user.cartaSalirDeLaCarcel) {
        user.cartaSalirDeLaCarcel = true;
        return user; 
    }
}

User GastarCartaSalirDeLaCarcel(User user) {
    if (user.cartaSalirDeLaCarcel) {
        user.cartaSalirDeLaCarcel = false;
        return user; 
    }
}