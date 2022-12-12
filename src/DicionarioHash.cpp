#include "DicionarioHash.hpp"
#include <iostream>

DicionarioHash::DicionarioHash(int _tamanho) : Dicionario(_tamanho)
{
    this->dicionario = new ListaEncadeada[53];

    for (int i = 0; i < 53; i++)
    {
        this->dicionario[i] = ListaEncadeada();
    }
}

DicionarioHash::~DicionarioHash()
{
    delete[] this->dicionario;
}

int DicionarioHash::Hash(std::string _verbete)
{
    char hashing = _verbete[0];
    if ((int)hashing < 91)
    {
        return int(hashing) - 65;
    }
    else if ((int)hashing > 96)
    {
        return int(hashing) - 71;
    }

    throw "Erro";
}

void DicionarioHash::imprimeDic(std::ostream &outfile)
{
    for (int i = 0; i < 53; i++)
    {
        dicionario[i].print(outfile);
    }
}

void DicionarioHash::removeDic()
{
    for (int i = 0; i < 53; i++)
    {
        dicionario[i].removeVerbetes();
    }
}

void DicionarioHash::insere(Verbete it)
{
    int pos;
    int aux;

    pos = Hash(it.getVerbete());
    aux = dicionario[pos].pesquisa(it.getVerbete(), it.getSignificado(), it.getType());

    if (aux == 0 || aux == 1)
    {
        dicionario[pos].insere(it);
    }
}