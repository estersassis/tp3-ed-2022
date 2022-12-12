#ifndef DICIONARIO_H
#define DICIONARIO_H
#include "Verbete.hpp"
#include <string>

class Dicionario {

    protected:
        int tamanho;

    public:
        Dicionario(int tamanho);

        virtual void insere(Verbete it) = 0;
        virtual void imprimeDic(std::ostream &outfile) = 0;
        virtual void removeDic() = 0;

};

#endif


