#ifndef CELULA_H
#define CELULA_H
#include <string>

class Celula {

    private:
        Celula *prox;

    public:
        Celula() {
            prox = NULL;
        };
};

#endif