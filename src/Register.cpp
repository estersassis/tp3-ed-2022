#include "Register.hpp"
#include <iostream>

Register::Register(){}

Register::Register(int _key) {
    this->key=_key;
}

int Register::getKey() {
    return this->key;
}