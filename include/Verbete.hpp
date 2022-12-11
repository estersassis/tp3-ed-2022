#ifndef VERBETE_H
#define VERBETE_H
#include "FilaSignificado.hpp"
#include <string>

class Verbete {

    private:
        char tipo;
        std::string verbete;
        FilaSignificado fila;

    public:
        Verbete();
        Verbete(Verbete &_item);

        void print();
        std::string getVerbete();
        void setVerbete(char _tipo, std::string _verbete); 
        void insertSiginificado(std::string _text);
};

#endif
