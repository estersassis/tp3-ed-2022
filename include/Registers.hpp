#ifndef REGISTERS_H
#define REGISTERS_H
#include <string>
#include "Register.hpp"

class Registers
{

    public:
        Registers(int seed, int N);
        ~Registers();

        int getSize();
        
        void partition(int Left, int Right, int *i, int *j);
        void ordination(int Left, int Right);

        void selectSort(Register *v, int m);
        void quickSortRecursive();
        void quickSortMedian(int k);
        void quickSortSelection(int m);
        void quickSortNonRecursive();
        void quickSortSmartStack();
        void mergeSort();
        void heapSort();

        void testing();
        
    private:
        Register *regs;
        int N;

        int compValue;
        int copyValue;
        double totalTime;

};
#endif