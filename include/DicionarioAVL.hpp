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

        void insere(Verbete it);
        void imprimeDic(std::ostream &outfile);
        void removeDic();

        Node *rotations(Node *_node, std::string type);
        Node *balance(Node *_node);
        Node *balanceTree(Node *_node);
        Node *insereRecursive(Node *_node, Verbete it);
        Node *removeRecursive(Node *_node, std::string key);
        Node *minValueNode(Node *_node);
        void pesquisaMain();
        void removeDicNode(Node *temp);
        void pesquisaRecursive(Node *_node);
        int diff(Node *temp);
        int altura(Node *temp);
        void imprimeRecursive(Node *_node, std::ostream &outfile);
};

#endif
