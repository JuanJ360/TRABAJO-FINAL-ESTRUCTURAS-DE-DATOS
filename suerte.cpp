#include "Suerte.h"

Suerte IniciarSuerte() {

    std::vector<CartaSuerte> vCartas;
    std::ifstream archivo("viernes13/CartasSuerte.json");

    if (archivo.is_open()) {

        json j;
        archivo >> j;

        for (int i = 0; i < j.size(); i++) {
            vCartas.push_back(
                CrearCartaSuerte(
                    j[i]["tipo"],
                    j[i]["nombre"],
                    j[i]["mensaje"]
                )
            );
        }

        // Barajar
        std::random_device rd;
        std::mt19937 gen(rd());
        std::shuffle(vCartas.begin(), vCartas.end(), gen);

        Suerte s;

        for (int i = 0; i < vCartas.size(); i++) {
            s.colaCartas.push(vCartas[i]);
        }

        return s;
    }

    else {
        throw std::runtime_error("IniciarSuerte: No se pudo abrir el archivo JSON");
    }
}

CartaSuerte SacarCartaSuerte(Suerte& s) {
    CartaSuerte carta = s.colaCartas.front();
    s.colaCartas.pop();
    s.colaCartas.push(carta); // vuelve al final

    return carta;
}
