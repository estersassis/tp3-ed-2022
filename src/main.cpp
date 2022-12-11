#include <iostream>
#include "FilaSignificado.hpp"
#include "Significado.hpp"
#include "Verbete.hpp"
#include "DicionarioHash.hpp"
#include "ListaEncadeada.hpp"

int main() {

    ListaEncadeada test;

    Verbete verb;
    verb.setVerbete('a', "balface");
    verb.insertSiginificado("Alfaces são boas apenas com molho Caeser.");
 
    test.insere(verb);
    test.print();

}