#include "Verbete.hpp"
#include "Significado.hpp"
#include <iostream>

Verbete::Verbete(){}

void Verbete::setVerbete(char _tipo, std::string _verbete) {
    this->tipo = _tipo;
    this->verbete = _verbete;
}

void Verbete::insertSiginificado(std::string _text) {
    Significado novo;
    novo.setText(_text);

    this->fila.enfileira(novo);
}

void Verbete::print() {
    std::cout << this->verbete << "(" << this->tipo << ")" << std::endl;
    this->fila.print();
}