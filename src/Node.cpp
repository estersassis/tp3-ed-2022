#include "Node.hpp"

Node::Node(){
    this->esquerda = NULL;
    this->direita = NULL;

    this->v.setVerbete("");
}

void Node::setVerbete(Verbete _v) {
    this->v = _v;
}

std::string Node::getVerbetText()
{
    return this->v.getVerbete();
}