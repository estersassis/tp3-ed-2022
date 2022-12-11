#include <iostream>
#include "FilaSignificado.hpp"
#include "Significado.hpp"
#include "Verbete.hpp"

int main() {
    
    Verbete test;

    test.setVerbete('a', "Testinho");
    
    test.insertSiginificado("Testando 1");
    test.insertSiginificado("Testando 2");

    test.print();
}