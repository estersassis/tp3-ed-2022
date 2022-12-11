#ifndef VERBETE_H
#define VERBETE_H
#include <string>
#include "Significado.hpp"

class Verbete {

    private:
        char tipo;
        std::string verbete;
        int n, tam;
        Significado *significados;

    public:
        Verbete(int _n);
        Verbete();

        void print();

        std::string getVerbete();
        int getTam();
        void setTipo(char _tipo);
        void setVerbete(std::string _verbete);

        void insertSiginificado(Significado _significado);
};

#endif
