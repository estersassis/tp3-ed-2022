#include "Significado.hpp"
#include <iostream>

Significado::Significado(std::string _text) {
    this->text = _text;
}

std::string Significado::getText() {
    return this->text;
}