#ifndef DICIONARIOHASH_H
#define DICIONARIOHASH_H
#include "Verbete.hpp"
#include "Dicionario.hpp"
#include "ListaEncadeada.hpp"
#include <string>

class DicionarioHash: Dicionario {

    private:
        ListaEncadeada *dicionario;

    public:
        DicionarioHash(int _tamanho);
        ~DicionarioHash();

        int Hash(std::string _verbete);
        int pesquisa(std::string _verbete);
        void insere(Verbete it);
        void imprimeDic();
        void removeDic();
        
};

#endif
