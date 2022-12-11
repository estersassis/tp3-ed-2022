#include "DicionarioHash.hpp"
#include <iostream>

DicionarioHash::DicionarioHash(int _tamanho) : Dicionario(_tamanho)
{
    this->dicionario = new ListaEncadeada[26];

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

Verbete DicionarioHash::pesquisa(std::string _verbete)
{
    int pos;
    Verbete item;
    pos = Hash(_verbete);
    item = dicionario[pos].pesquisa(_verbete);
    return item;
}

void DicionarioHash::insere(Verbete *it)
{
    int pos;
    Verbete aux;

    aux = this->pesquisa(it->getVerbete());
    std::cout << "wwwwwwwww" << std::endl;

    if (aux.getVerbete() != "")
        pos = Hash(it->getVerbete());
    dicionario[pos].insere(*it);
}