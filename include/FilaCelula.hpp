#ifndef FILACELULA_H
#define FILACELULA_H
#include "Significado.hpp"
#include <string>

class FilaCelula {

    private:
        Significado item;
        FilaCelula *prox;

    public:
        FilaCelula();
    
    friend class FilaSignificado;
};

#endif