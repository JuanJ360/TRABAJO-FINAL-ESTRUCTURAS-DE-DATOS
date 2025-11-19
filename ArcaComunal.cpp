#include "ArcaComunal.h"

ArcaComunal IniciarArcaComunal() {

    std::vector<CartaArcaComunal> vCartas;
    std::ifstream archivo("viernes13/CartasArcaComunal.json");
    
    if (archivo.is_open()) {

        json j;
        archivo >> j; // se lee el archivo en la variable j de tipo json

        for (int i = 0; i < j.size(); i++) {
            vCartas.push_back(CrearCartaArcaComunal(j[i]["tipo"], j[i]["nombre"], j[i]["mensaje"]));
        }
        
        // revolver el vector de las cartas con shuffle
        std::random_device rd; 
        std::mt19937 gen(rd());
        std::shuffle(vCartas.begin(), vCartas.end(), gen);

        ArcaComunal ac;

        for (int i = 0; i < vCartas.size(); i++) {
            ac.colaCartas.push(vCartas[i]);
        }

        return ac;
    }

    else {
        throw std::runtime_error("IniciarArcaComunal: El archivo json no se ha abierto correctamente");
    }
}

CartaArcaComunal SacarCartaArcaComunal(ArcaComunal& ac) {
    CartaArcaComunal carta = ac.colaCartas.front();
    ac.colaCartas.pop();
    ac.colaCartas.push(carta); // el profe dijo en el pdf que las cartas se vuelven a agrergar al final de la cola

    return carta;
}