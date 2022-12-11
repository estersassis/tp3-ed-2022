#ifndef LISTACELULA_H
#define LISTACELULA_H
#include "Verbete.hpp"
#include <string>

class ListaCelula {

    private:
        Verbete item;
        ListaCelula *prox;

    public:
        ListaCelula();

        friend class ListaEncadeada;
};

#endif