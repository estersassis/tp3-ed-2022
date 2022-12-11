#ifndef DICIONARIO_H
#define DICIONARIO_H
#include "Verbete.hpp"
#include <string>

class Dicionario {

    protected:
        int tamanho;

    public:
        Dicionario(int tamanho);

        virtual int pesquisa(std::string _verbete) = 0;
        virtual void insere(Verbete it) = 0;
        virtual void imprimeDic() = 0;
        // virtual int atualizaDic(Verbete *it) = 0;
        virtual void removeDic() = 0;

};

#endif


