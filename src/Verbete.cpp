#include "Verbete.hpp"
#include "Significado.hpp"
#include <iostream>

Verbete::Verbete(){}

Verbete::Verbete(Verbete &_item)
{
    this->tipo = _item.tipo;
    this->verbete = _item.verbete;

    FilaCelula *p;
    Significado aux;
    p = _item.fila.frente->prox;

    while (p != NULL)
    {
        aux.setText(p->item.getText());
        this->fila.enfileira(aux);
        
        p = p->prox;
    }
}

std::string Verbete::getVerbete()
{
    return this->verbete;
}

void Verbete::setVerbete(char _tipo, std::string _verbete)
{
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