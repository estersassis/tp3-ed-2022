#include "DicionarioAVL.hpp"
#include <iostream>


DicionarioAVL::DicionarioAVL(int _tamanho) : Dicionario(_tamanho)
{
    this->root = NULL;
    this->temp1 = NULL;
}

DicionarioAVL::~DicionarioAVL()
{
    delete this->root;
    delete this->temp1;
}

void DicionarioAVL::insere(Verbete it)
{
    insereRecursive(this->root, it);
}

Node *DicionarioAVL::insereRecursive(Node *_node, Verbete it)
{

    if (this->root == NULL)
    {
        root = new Node();
        root->v = it;

        return root;
    }
    else
    {
        if (it.getVerbete() < _node->getVerbetText())
        {
            _node->esquerda = insereRecursive(
                _node->esquerda, _node->v);
        }

        else if (it.getVerbete() > _node->getVerbetText())
        {
            _node->direita = insereRecursive(
                _node->direita, _node->v);
        }
        else  {
            throw "Erro: existe ja";
        }
    }
    return _node;
}

void DicionarioAVL::imprimeDic() 
{
    imprimeRecursive(this->root);
}

void DicionarioAVL::imprimeRecursive(Node *_node)
{
    if (_node == NULL)
        return;
    imprimeRecursive(_node->esquerda);
    _node->v.print();

    imprimeRecursive(_node->direita);
}

int DicionarioAVL::pesquisa(std::string _verbete){
    return -1;
}

void DicionarioAVL::removeDic()
{
    return;
}