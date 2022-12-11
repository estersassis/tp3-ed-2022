#include <iostream>
#include "Significado.hpp"
#include "Verbete.hpp"
#include "DicionarioHash.hpp"
#include "ListaEncadeada.hpp"

int main() {

    Significado a;
    a.setText("Batatas salgadas comem jujubas");
    Significado b;
    b.setText("Escorpioes são senhorinhas");
    Significado c;
    c.setText("Amamos cogumelos do sul de Marte");


    Verbete d(10);
    d.setTipo('a');
    d.setVerbete("amoras");
    d.insertSiginificado(a);
    d.insertSiginificado(b);

    Verbete f(10);
    f.setTipo('a');
    f.setVerbete("botas");
    f.insertSiginificado(c);

    ListaEncadeada e;
    e.insere(f);
    e.insere(d);
    

    e.print();

}