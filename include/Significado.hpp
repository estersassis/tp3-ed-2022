#ifndef SIGNIFICADO_H
#define SIGNIFICADO_H
#include <string>

class Significado {

    private:
        std::string text;

    public:
        Significado();
        std::string getText();
        void setText(std::string _text);
};

#endif