#ifndef FILACELULA_H
#define FILACELULA_H
#include "Significado.hpp"
#include "FilaSignificado.hpp"
#include <string>

class FilaCelula {

    private:
        Significado item;
        FilaCelula *prox;

    public:
        FilaCelula() {
            this->item.setText("");
            prox = NULL;
        };
    
    friend class FilaSignificado;
};

#endif