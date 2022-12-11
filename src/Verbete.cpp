#include "Verbete.hpp"
#include "Significado.hpp"
#include <iostream>

Verbete::Verbete(int _n) {
    this->n = _n;
    this->tam = 0;
    this->tipo = '?';
    this->verbete = "";

    this->significados = new Significado[_n];

    for (int i = 0; i < _n; i++) {
        this->significados[i] = Significado();
    }
}
Verbete::Verbete()
{
    this->tam = 0;

    this->significados = new Significado[1];
    this->significados[0] = Significado();

}

std::string Verbete::getVerbete()
{
    return this->verbete;
}

void Verbete::setTipo(char _tipo)
{
    this->tipo = _tipo;
}

void Verbete::setVerbete(std::string _verbete)
{
    this->verbete = _verbete;
}

void Verbete::insertSiginificado(Significado _significado)
{
    this->significados[tam] = _significado;
    tam++;  
}

void Verbete::print() {
    std::cout << this->verbete << "(" << this->tipo << ")" << std::endl;
    
    for (int i = 0; i < tam; i++)
    {
        int num = i + 1;
        std::cout << num << ". " << this->significados[i].getText() << std::endl;
    }
    
}