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

void DicionarioHash::imprimeDic(std::ostream &outfile)
{
    for (int i = 0; i < 27; i++)
    {
        dicionario[i].print(outfile);
    }
    
}

void DicionarioHash::removeDic()
{
    for (int i = 0; i < 27; i++)
    {
        dicionario[i].removeVerbetes();
    }
}

void DicionarioHash::insere(Verbete it)
{
    int pos;
    int aux;

    pos = Hash(it.getVerbete());
    aux = dicionario[pos].pesquisa(it.getVerbete(), it.getSignificado());

    if (aux == 0) {
        dicionario[pos].insere(it);
    }
}