#ifndef DICIONARIOAVL_H
#define DICIONARIOAVL_H
#include "Verbete.hpp"
#include "Dicionario.hpp"
#include "Node.hpp"
#include <string>

class DicionarioAVL : Dicionario
{

    private:
        Node *root;
        Node *temp1;

    public:
        DicionarioAVL(int _tamanho);
        ~DicionarioAVL();

        int pesquisa(std::string _verbete);
        void insere(Verbete it);
        void imprimeDic();
        void removeDic();

        Node *rotations(Node *_node, char type);
        Node *balance(Node *_node);
        Node *balanceTree(Node *_node);
        Node *insereRecursive(Node *_node, Verbete it);
        void imprimeRecursive(Node *_node);
};

#endif
