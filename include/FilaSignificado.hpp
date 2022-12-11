#ifndef FILASIGNIFICADO_H
#define FILASIGNIFICADO_H
#include "FilaCelula.hpp"
#include "Significado.hpp"
#include <string>

class FilaSignificado {

    private:
        FilaCelula* frente;
        FilaCelula* tras;
        int tamanho;

    public:
        FilaSignificado();
        virtual ~FilaSignificado();

        void enfileira(Significado item);
        void limpa();
        void print();
    
    friend class Verbete;
};

#endif