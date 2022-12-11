#include <iostream>
#include "FilaSignificado.hpp"
#include "Significado.hpp"
#include "Verbete.hpp"
#include "DicionarioHash.hpp"

int main() {
    
    DicionarioHash dic(100);
    dic.Hash("abcdefghijklmnopqrstuvwxyz");
}