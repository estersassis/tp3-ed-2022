#ifndef DICIONARIO_H
#define DICIONARIO_H
#include "Verbete.hpp"
#include <string>

class Dicionario {

    public:
        Dicionario *criaDic(int N);
        virtual int pesquisaDic(Dicionario *dic, Verbete *it){return -1;};
        virtual int insereDic(Dicionario *dic, Verbete *it){return -1;};
        virtual int imprimeDic(Dicionario *dic){return -1;};
        virtual int atualizaDic(Dicionario *dic, Verbete *it){return -1;};
        virtual int removeDic(Dicionario *dic, Verbete *it){return -1;};
        virtual int destroiDic(Dicionario *dic){return -1;};

};

#endif


