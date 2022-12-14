#ifndef VERBETE_H
#define VERBETE_H
#include <string>
#include "Significado.hpp"

class Verbete {

    private:
        char type;
        std::string verbete;
        int size, qtd_significados;
        Significado *significados;

    public:
        Verbete(int _size);
        Verbete();

        char getType();
        std::string getVerbete();
        int getQtdSignificados();
        Significado getFirstSignificado();

        void setType(char _type);
        void setVerbete(std::string _verbete);

        void printOut(std::ostream &outfile);
        void insertSiginificado(Significado _significado);
};

#endif
