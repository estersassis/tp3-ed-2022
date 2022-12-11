#include "DicionarioHash.hpp"
#include <iostream>

DicionarioHash::DicionarioHash(int _tamanho) : Dicionario(_tamanho)
{
    this->dicionario = new ListaEncadeada[26];
}

DicionarioHash::~DicionarioHash() {
    delete this->dicionario;
}

int DicionarioHash::Hash(std::string _verbete) {
    return int(_verbete[0]);
}

// Verbete DicionarioHash::pesquisa(std::string _verbete)
// {
//     int pos;
//     Verbete item;
//     pos = Hash(_verbete);
//     item = this->dicionario[pos].pesquisa(_verbete);
//     return item;
// }
