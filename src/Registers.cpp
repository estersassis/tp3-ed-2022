#include "Registers.hpp"
#include <iostream>


Registers::Registers(int seed, int N) {
    this->N = N;
    this->regs = new Register[N];

    srand(seed);
    for (int i = 0; i < N; i++) {
        int random = rand();
        this->regs[i] = Register(random);
    }
}

Registers::~Registers(){}

void Registers::testing() {
    for (int i = 0; i < this->N; i++) {
        std::cout << this->regs[i].getKey() << std::endl;
    }
    
}