#include "ArcaComunal.h"

ArcaComunal IniciarArcaComunal() {
    std::vector<CartaArcaComunal> vCartas = {
        {"Ganancia", "Error del Banco a favor", "Error del Banco a tu favor. Cobra $200."},
        {"Movimiento", "Adelántese a la Salida", "Adelántese a la casilla de Salida. Cobra $200."},
        {"Especial", "Salga Gratis de la Cárcel", "Salga Gratis de la Cárcel. Conserve esta tarjeta hasta que la necesite o la venda."},
        {"Gasto", "Honorarios del médico", "Pague la factura del médico $50."},
        {"Gasto", "Cuota escolar", "Pague la cuota escolar $150."},
        {"Gasto", "Póliza de seguro de vida", "Pague la póliza de seguro de vida $100."},
        {"Gasto", "Reembolso de impuestos", "Reembolso de impuestos. Cobra $20."},
        {"Ganancia", "Herencia", "Recibe una herencia. Cobra $100."},
        {"Ganancia", "Segundo premio de belleza", "Ha ganado el segundo premio en un concurso de belleza. Cobra $10."},
        {"Ganancia", "Venta de acciones", "De la venta de sus acciones recibe $45."},
        {"Ganancia", "Recibe renta", "Recibe la renta del vencimiento de acciones. Cobra $50."},
        {"Gasto (Gral)", "Reparaciones en la calle", "Pague una evaluación especial por cada casa $40. Pague por cada hotel $115."},
        {"Movimiento", "Ir a la Cárcel", "Vaya a la Cárcel. Vaya directamente. No pase por Salida. No cobre los $200."},
        {"Ganancia (Gral)", "Aniversario", "Es su aniversario. Cada jugador le da $10."},
        {"Ganancia", "Regalo de Navidad", "Navidad llega tarde, recibe $100."},
        {"Ganancia", "Nuevo apartamento", "Te has mudado a un nuevo departamento. Cobra $20."}
    };
    
    // revolver el vector de las cartas
    std::random_device rd; 
    std::mt19937 generador(rd());
    std::shuffle(vCartas.begin(), vCartas.end(), generador());

    ArcaComunal ac;

    for (int i = 0; i < vCartas.size(); i++) {
        ac.colaCartas.push(vCartas[i]);
    }

    return ac;
}

CartaArcaComunal SacarCartaArcaComunal(ArcaComunal& ac) {
    CartaArcaComunal carta = ac.colaCartas.front();
    ac.colaCartas.pop();
    ac.colaCartas.push(carta); // el profe dijo en el pdf que las cartas se vuelven a agrergar al final de la cola

    return carta;
}