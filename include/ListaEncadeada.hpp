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

        int pesquisa(std::string c, Significado sig, char tipo);
        void insere(Verbete item);
        int discoverPosition(std::string _verbete, char tipo);
        void remove(std::string _verbete, char _tipo);
        void removeVerbetes();

        void limpa();
        void print(std::ostream &outfile);
};

#endif