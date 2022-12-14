#include "Verbete.hpp"
#include "Significado.hpp"
#include <iostream>

Verbete::Verbete(int _size) {
    this->size = _size;

    this->qtd_significados = 0;
    this->type = '?';
    this->verbete = "";

    this->significados = new Significado[_size];
    for (int i = 0; i < _size; i++) {
        this->significados[i] = Significado();
    }
}

Verbete::Verbete() {
    this->qtd_significados = 0;
    this->verbete = "";

    this->significados = new Significado[1];
    this->significados[0] = Significado();

}

int Verbete::getQtdSignificados() {
    return this->qtd_significados;
}

char Verbete::getType() {
    return this->type;
}

std::string Verbete::getVerbete() {
    return this->verbete;
}

Significado Verbete::getFirstSignificado() {
    return this->significados[0];
}

void Verbete::setType(char _type) {
    this->type = _type;
}

void Verbete::setVerbete(std::string _verbete) {
    this->verbete = _verbete;
}

void Verbete::insertSiginificado(Significado _significado) {
    this->significados[qtd_significados] = _significado;

    qtd_significados++;  
}

void Verbete::printOut(std::ostream &outfile) {

    outfile << this->verbete.c_str() << " (" << this->type << ")" << std::endl;

    for (int i = 0; i < qtd_significados; i++) {
        int num = i + 1;

        if (this->significados[i].getText() != "") {
            outfile << num << ". " << this->significados[i].getText() << std::endl;
        }
    }
}