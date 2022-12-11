#ifndef NODE_H
#define NODE_H
#include "Verbete.hpp"
#include "Dicionario.hpp"
#include <string>

class Node
{
    private:
        Verbete v;
        int altura;

        Node* esquerda;
        Node* direita;

    public:
        Node();

        void setVerbete(Verbete _v);
        std::string getVerbetText();

    friend class DicionarioAVL;
};

#endif
