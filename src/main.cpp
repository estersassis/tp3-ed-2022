#include <iostream>
#include "FilaSignificado.hpp"
#include "Significado.hpp"

int main() {
    Significado test;
    test.setText("Testando eficiencia.");

    Significado test2;
    test2.setText("Testando eficiencia 2.");

    FilaSignificado fila;
    fila.enfileira(test);
    fila.enfileira(test2);

    fila.limpa();

    fila.print();
}