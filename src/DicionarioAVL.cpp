#include "DicionarioAVL.hpp"
#include <iostream>


DicionarioAVL::DicionarioAVL(int _tamanho) : Dicionario(_tamanho)
{
    this->root = new Node();
    this->temp1 = new Node();
}

DicionarioAVL::~DicionarioAVL()
{
    delete this->root;
    delete this->temp1;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

void DicionarioAVL::insere(Verbete it)
{
    insereRecursive(this->root, it);
    this->root = balanceTree(this->root);
}

int DicionarioAVL::altura(Node *temp) {
    int h = 0;
    if (temp != NULL)
    {
        int l_height = altura(temp->esquerda);
        int r_height = altura(temp->direita);
        int max_height;

        max_height = max(r_height, l_height);

        h = max_height + 1;
    }
    return h;
}

int DicionarioAVL::diff(Node *temp)
{
    int l_height = altura(temp->esquerda);
    int r_height = altura(temp->direita);
    int b_factor = l_height - r_height;

    return b_factor;
}

Node *DicionarioAVL::rotations(Node *_node, std::string type) {
    Node *temp;

    if (type == "rr")
    {
        temp = _node->direita;
        _node->direita = temp->esquerda;
        temp->esquerda = _node;

        return temp;
    }
    else if (type == "ll")
    {
        temp = _node->esquerda;
        _node->esquerda = temp->direita;
        temp->direita = _node;

        return temp;
    }
    else if(type == "lr")
    {
        temp = _node->esquerda;
        _node->esquerda = rotations(temp, "rr");
        return rotations(_node, "ll");
    }
    else if (type == "rl")
    {
        temp = _node->direita;
        _node->direita = rotations(temp, "ll");
        return rotations(_node, "rr");
    }
    return _node;
}

Node *DicionarioAVL::balance(Node *_node)
{
    int bal_factor = diff(_node);

    if (bal_factor > 1)
    {
        if (diff(_node->esquerda) > 0)
        {
            _node = rotations(_node, "ll");
        }

        else
        {
            _node = rotations(_node, "lr");
        }
    }
    else if (bal_factor < -1)
    {
        if (diff(_node->direita) > 0)
        {
            _node = rotations(_node, "rl");
        }

        else
        {
            _node = rotations(_node, "rr");
        }
    }

    return _node;
}

Node *DicionarioAVL::balanceTree(Node *_node)
{
    if (_node == NULL)
    {
        return NULL;
    }

    _node->esquerda = balanceTree(_node->esquerda);

    _node->direita = balanceTree(_node->direita);

    _node = balance(_node);
    return _node;
}

Node *DicionarioAVL::insereRecursive(Node *_node, Verbete it)
{
    if (_node == NULL)
    {
        _node = new Node();
        _node->v = it;
        return _node;
    }
    else if (_node->v.getVerbete() == "")
    {
        _node->v = it;
        return _node;
    }
    else
    {
        if (it.getVerbete() < _node->v.getVerbete())
        {
            _node->esquerda = insereRecursive(
                _node->esquerda, it);
        }

        else if (it.getVerbete() > _node->v.getVerbete())
        {
            _node->direita = insereRecursive(
                _node->direita, it);
        }
        else  {
            if (_node->v.getType() == it.getType())
            {
                _node->v.insertSiginificado(it.getSignificado());
            }
            else {
                _node->direita = insereRecursive(
                    _node->direita, it);
            }
            
        }
    }
    return _node;
}

void DicionarioAVL::imprimeDic(std::ostream &outfile)
{
    imprimeRecursive(this->root, outfile);
}

void DicionarioAVL::imprimeRecursive(Node *_node, std::ostream &outfile)
{
    if (_node == NULL)
    {
        return;
    }
    
    if (_node->direita == NULL && _node->esquerda == NULL) {
        _node->v.print(outfile);
        return;
    }
    imprimeRecursive(_node->esquerda, outfile);
    _node->v.print(outfile);
    imprimeRecursive(_node->direita, outfile);
}

void DicionarioAVL::removeDic()
{
    for (int i = 0; i < tamanho; i++)
    {
        pesquisaRecursive(this->root);
    }
    // 
}

void DicionarioAVL::pesquisaRecursive(Node *_node){
    if (_node == NULL) {
        return;
    }

    else if (_node->v.getTam() > 0)
    {
        removeDicNode(_node);
        return;
    }

    pesquisaRecursive(_node->esquerda);
    pesquisaRecursive(_node->direita);
}

Node *DicionarioAVL::minValueNode(Node *node)
{
    Node *current = node;

    while (current->esquerda != NULL)
        current = current->esquerda;

    return current;
}

Node *DicionarioAVL::removeRecursive(Node *_node, std::string key, char tipo){
   
    if (_node == NULL)
        return _node;

    if (key < _node->v.getVerbete())
        _node->esquerda = removeRecursive(_node->esquerda, key, tipo);

    else if (key > _node->v.getVerbete())
        _node->direita = removeRecursive(_node->direita, key, tipo);

    else {
        if (_node->v.getType() == tipo)
        {

            if (_node->direita == NULL && _node->esquerda == NULL)
            {
                return NULL;
            }
            else if (_node->esquerda == NULL)
            {
                return _node->direita;
            }
            else if (_node->direita == NULL)
            {
                return _node->esquerda;
            }

            else
            {
                Node *temp = minValueNode(_node->direita);
                _node->v = temp->v;
                _node->direita = removeRecursive(_node->direita,
                                                 temp->v.getVerbete(), temp->v.getType());
            }
        }
        else {
            _node->direita = removeRecursive(_node->direita, key, tipo);
            _node->esquerda = removeRecursive(_node->esquerda, key, tipo);
        }

    }


    return _node;
}

void DicionarioAVL::removeDicNode(Node *_node)
{
    this->root = removeRecursive(this->root, _node->v.getVerbete(), _node->v.getType());
    balance(this->root);
}