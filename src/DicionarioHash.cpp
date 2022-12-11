#include "DicionarioHash.hpp"
#include <iostream>

DicionarioHash::DicionarioHash(int _tamanho) : Dicionario(_tamanho)
{
    this->dicionario = new ListaEncadeada[27];

    for (int i = 0; i < 26; i++)
    {
        this->dicionario[i] = ListaEncadeada();
    }
}

DicionarioHash::~DicionarioHash() {
    delete[] this->dicionario;
}

int DicionarioHash::Hash(std::string _verbete) {
    char hashing = tolower(_verbete[0]);
    return int(hashing) - 97;
}

void DicionarioHash::imprimeDic()
{
    for (int i = 0; i < 27; i++)
    {
        dicionario[i].print();
    }
    
}

void DicionarioHash::removeDic()
{
    for (int i = 0; i < 27; i++)
    {
        dicionario[i].removeVerbetes();
    }
}

int DicionarioHash::pesquisa(std::string _verbete)
{
    int pos;
    Verbete item;
    pos = Hash(_verbete);
    item = dicionario[pos].pesquisa(_verbete);

    if (item.getVerbete() != "") {
        return -1;
    }

    return 0;
}

void DicionarioHash::insere(Verbete it)
{
    int pos;
    int aux;

    aux = this->pesquisa(it.getVerbete());

    if (aux == 0) {
        pos = Hash(it.getVerbete());
        dicionario[pos].insere(it);
    }
}