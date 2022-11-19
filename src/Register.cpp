#include "Register.hpp"
#include <iostream>

Register::Register(){}

Register::Register(int _key) {
    this->key=_key;

    for (int i = 0; i < 10; i++) {
        this->num[i] = 0;
    }

    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 200; j++) {
            this->ch[i][j] = 'a';
        }
    }
}

int Register::getKey() {
    return this->key;
}