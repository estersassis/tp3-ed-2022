#include "ListaEncadeada.hpp"

ListaEncadeada::ListaEncadeada()
{
    this->tamanho = 0;
}

ListaEncadeada::~ListaEncadeada()
{
    delete this->primeiro;
    delete this->ultimo;
}