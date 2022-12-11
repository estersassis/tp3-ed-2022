#include <iostream>
#include "Significado.hpp"
#include "Verbete.hpp"
#include "DicionarioHash.hpp"
#include "DicionarioAVL.hpp"
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

    Verbete g(10);
    g.setTipo('a');
    g.setVerbete("batas");

    Verbete f(10);
    f.setTipo('a');
    f.setVerbete("botas");
    f.insertSiginificado(c);

    // ListaEncadeada e;
    // e.insere(f);
    // e.insere(d);
    // e.insere(g);

    // e.print();
    // std::cout << "--------------------------" << std::endl;
    // e.removeVerbetes();
    // e.print();

    // DicionarioHash h(10);
    // h.insere(d);
    // h.insere(f);
    // h.insere(g);
    // h.imprimeDic();
    // std::cout << "--------------------------" << std::endl;
    // h.removeDic();
    // h.imprimeDic();

    DicionarioAVL avl(10);

    avl.insere(d);
    avl.insere(f);
    avl.insere(g);
    avl.imprimeDic();
}