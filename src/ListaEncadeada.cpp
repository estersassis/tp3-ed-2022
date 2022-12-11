#include "ListaEncadeada.hpp"
#include <iostream>


ListaEncadeada::ListaEncadeada()
{
    this->tamanho = 0;
    this->primeiro = new ListaCelula();
    this->ultimo = primeiro;
}

ListaEncadeada::~ListaEncadeada()
{
    limpa();
    delete this->primeiro;
}

void ListaEncadeada::limpa()
{
    ListaCelula *p;
    p = primeiro->prox;

    while (p != NULL)
    {
        primeiro->prox = p->prox;
        delete p;
        p = primeiro->prox;
    }

    ultimo = primeiro;
    tamanho = 0;
}

Verbete ListaEncadeada::pesquisa(std::string c) {
    Verbete aux;
    ListaCelula *p;
    p = primeiro->prox;
    while (p != NULL)
    {
        if (p->item.getVerbete() == c)
        {
            aux = p->item;
            break;
        }
        p = p->prox;
    }
    return aux;

}

ListaCelula *ListaEncadeada::posiciona(int pos, bool antes = false)
{
    ListaCelula *p;
    int i;
    if ((pos > tamanho) || (pos == 0))
        return primeiro;
    
    p = primeiro;
    for (i = 0; i < pos; i++)
    {
        p = p->prox;
    }
    
    if (!antes)
        p = p->prox;
    return p;
}

int ListaEncadeada::discoverPosition(std::string _verbete)
{
    ListaCelula *p;
    p = this->primeiro;

    int count = 0;

    while (p->prox != NULL && p->prox->item.getVerbete() < _verbete)
    {
        p = p->prox;
        count++;
    }

    return count;
}

void ListaEncadeada::insere(Verbete item)
{
    int pos = this->discoverPosition(item.getVerbete());
    
    ListaCelula *p, *nova;
    p = posiciona(pos, true);

    nova = new ListaCelula();
    nova->item = item;
    
    nova->prox = p->prox;
    p->prox = nova;
    
    tamanho++;

    if (nova->prox == NULL)
        ultimo = nova;
    
};

void ListaEncadeada::print() {
    ListaCelula *p;
    p = primeiro;

    while (p->prox != NULL)
    {
        p->prox->item.print();
        p = p->prox;
    }

}