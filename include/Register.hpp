#ifndef REGISTER_H
#define REGISTER_H
#include <string>


class Register {

    public:
        Register();
        Register(int _key);

        int getKey();

    private:
        int key;
        int num[10];
        std::string ch[15][200];

};

#endif