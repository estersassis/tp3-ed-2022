#ifndef LISTAENCADEADA_H
#define LISTAENCADEADA_H
#include "ListaCelula.hpp"
#include "Verbete.hpp"
#include <string>

class ListaEncadeada
{
    private:
        ListaCelula *primeiro;
        ListaCelula *ultimo;
        int tamanho;

        ListaCelula *posiciona(int pos, bool antes);
        void inserePosicao(Verbete item, int pos);

    public:
        ListaEncadeada();
        // ~ListaEncadeada();

        Verbete pesquisa(std::string c);
        void insere(Verbete item);
        int discoverPosition(std::string _verbete);
        void remove(std::string _verbete);
        void removeVerbetes();

        void limpa();
        void print();
};

#endif