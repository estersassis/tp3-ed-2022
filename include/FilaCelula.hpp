#ifndef FILACELULA_H
#define FILACELULA_H
#include "Celula.hpp"
#include "Significado.hpp"
#include <string>

class FilaCelula: Celula {

    private:
        Significado item;

    public:
        FilaCelula(std::string _text) {
            this->item.setText(_text);
        };
};

#endif