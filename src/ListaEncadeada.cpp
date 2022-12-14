#include "ListaEncadeada.hpp"
#include <iostream>


ListaEncadeada::ListaEncadeada()
{
    this->tamanho = 0;
    this->primeiro = new ListaCelula();
    this->ultimo = primeiro;
}

// ListaEncadeada::~ListaEncadeada()
// {
//     limpa();
//     delete this->primeiro;
// }

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

void ListaEncadeada::remove(std::string _verbete, char _type) {
    Verbete aux;
    ListaCelula *p, *q;
    // Posiociona p na célula anterior ao item procurado
    p = primeiro;

    while (((p->prox != NULL) && (p->prox->item.getVerbete() != _verbete)) || (p->prox->item.getType() != _type)){
        p = p->prox;
    }
    // remove a célula contendo o item, retornando-o
    if (p->prox == NULL)
        throw "Erro: item não está presente";
    else
    {
        q = p->prox;
        p->prox = q->prox;
        aux = q->item;
        delete q;
        tamanho--;
        if (p->prox == NULL)
            ultimo = p;
    }
}

void ListaEncadeada::removeVerbetes() {
    ListaCelula *p;
    p = primeiro->prox;

    while (p != NULL)
    {
        if (p->item.getQtdSignificados() > 0)
        {
            this->remove(p->item.getVerbete(), p->item.getType());
        }
        
        p = p->prox;
    }
}

int ListaEncadeada::pesquisa(std::string c, Significado sig, char type)
{
    ListaCelula *p;
    p = primeiro->prox;
    int ret = -2;

    while (p != NULL)
    {
        
        if (p->item.getVerbete() == c)
        {
            if (p->item.getType() == type)
            {
                p->item.insertSiginificado(sig);
                ret = -1;
            }
            
            else {
                ret = 1;
            }
        }
        p = p->prox;
    }
    if (ret == -1)
        return ret;
    else if (ret == 1)
        return 1;
    
    return 0;
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

int ListaEncadeada::discoverPosition(std::string _verbete, char type)
{
    ListaCelula *p;
    p = this->primeiro;

    int count = 0;

    while (p->prox != NULL && p->prox->item.getVerbete() < _verbete)
    {
        p = p->prox;
        count++;
    }
    if (p->prox != NULL && p->prox->item.getVerbete() == _verbete)
    {
        p = p->prox;
        count++;
        if (p->prox != NULL && p->prox->item.getVerbete() == _verbete)
        {
            p = p->prox;
            count++;
        }
    }   

    return count;
}

void ListaEncadeada::insere(Verbete item)
{
    int pos = this->discoverPosition(item.getVerbete(), item.getType());

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

void ListaEncadeada::printOut(std::ostream &outfile)
{
    ListaCelula *p;
    p = primeiro;

    while (p->prox != NULL)
    {
        p->prox->item.printOut(outfile);
        p = p->prox;
    }
}