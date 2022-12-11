#include "FilaSignificado.hpp"
#include "Significado.hpp"
#include "FilaCelula.hpp"
#include <iostream>

FilaSignificado::FilaSignificado() {
    this->frente = new FilaCelula;
    this->tras = this->frente;
}

FilaSignificado::~FilaSignificado() {
    this->limpa();
    delete this->frente;
}

void FilaSignificado::enfileira(Significado item) {
    FilaCelula *nova;
    nova = new FilaCelula();

    nova->item = item;
    this->tras->prox = nova;
    this->tras = nova;

    tamanho++;
}

void FilaSignificado::limpa() {

    FilaCelula *p;
    p = frente->prox;
    while (p != NULL)
    {
        frente->prox = p->prox;
        delete p;
        p = frente->prox;
    }
    tamanho = 0;
    tras = frente;
}

void FilaSignificado::print() {

    FilaCelula *p;

    int i = 1;
    p = this->frente->prox;

    while (p != NULL)
    {
        std::cout << i << ". " << p->item.getText() << std::endl;
        p = p->prox;
        i++;
    }
}
