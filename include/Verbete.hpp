#ifndef VERBETE_H
#define VERBETE_H
#include "FilaSignificado.hpp"
#include <string>

class Verbete
{
    public:
        void print();

    private:
        char tipo;
        std::string verbete;
        FilaSignificado fila;
};

#endif
