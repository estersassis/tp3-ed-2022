#include <iostream>
#include "FilaSignificado.hpp"
#include "Significado.hpp"
#include "Verbete.hpp"
#include "DicionarioHash.hpp"
#include "ListaEncadeada.hpp"

int main() {

   
    DicionarioHash test(40);

    Verbete *verb = new Verbete();
    verb->setVerbete('a', "Depressao");

    test.insere(verb);

    delete verb;


}