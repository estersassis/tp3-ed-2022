#ifndef SIGNIFICADO_H
#define SIGNIFICADO_H
#include <string>

class Significado {

    private:
        std::string text;

    public:
        Significado(std::string _text);
        std::string getText();
};

#endif