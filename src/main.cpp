#include "Registers.hpp"
#include <iostream>

int main()
{
    int seed = 10;
    int N = 10;

    Registers test(seed, N);
    test.testing();
    test.mergeSort();
    std::cout << "Ording... ------------------" << std::endl;
    test.testing();

    
}