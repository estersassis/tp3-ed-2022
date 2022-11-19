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
        std::string getMetrics();

        void quickSortRecursive();
        void partitionRecursive(int left, int right, int *i, int *j);
        void ordinationRecursive(int left, int right);

        void quickSortMedian(int k);
        void partitionMedian(int left, int right, int *i, int *j, int k);
        void ordinationMedian(int left, int right, int k);
        int chooseRandonMedian(int k, int left, int right);

        void selectSort(int left, int right);
        void quickSortSelection(int m);
        void ordinationSelection(int left, int right, int m);

        void ordinationNonRecursive();
        void quickSortNonRecursive();

        void ordinationSmartStack();
        void quickSortSmartStack();

        void mergeSort();
        void merge(int left, int mid, int right);
        void ordinationMerge(int left, int right);

        void heapSort();
        void build();
        void remake(int left, int right);

        void testing();
        
    private:
        Register *regs;
        int N;

        int compValue;
        int copyValue;
        double totalTime;

};
#endif