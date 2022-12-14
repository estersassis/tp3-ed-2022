#include "Significado.hpp"

Significado::Significado() {}

std::string Significado::getText() {
    return this->text;
}

void Significado::setText(std::string _text) {
    this->text = _text;
}