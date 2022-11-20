#ifndef REGISTERS_H
#define REGISTERS_H
#include <string>
#include "Register.hpp"

class Registers
{

    public:
        Registers(int seed, int N);
        ~Registers();

        // Functions for metrics acess
        double getProcessingTime();
        int getComparisonsQtd();
        int getCopiesQtd();
        void restartMetrics();

        // Basic partiton function, uses middle element as pivot
        void partiton(int left, int right, int *i, int *j);

        // Functions to process padronized recursive quicksort
        void quickSortRecursive();
        void ordinationRecursive(int left, int right);

        // Funcions to process mediam recursive quicksort
        void quickSortMedian(int k);
        void ordinationMedian(int left, int right, int k);
        void partitionMedian(int left, int right, int *i, int *j, int k);
        int chooseRandonMedian(int k, int left, int right);

        // Funcions to process selection recursive quicksort
        void quickSortSelection(int m);
        void ordinationSelection(int left, int right, int m);
        void selectSort(int left, int right);
        
        // Funcions to process non recursive/interactive quicksort
        //obs.: follows always for the bigger side of the partition
        void quickSortNonRecursive();
        void ordinationNonRecursive();

        // Funcions to process non recursive/interactive smart quicksort
        // obs.: follows always for the shortest side of the partition
        void quickSortSmartStack();
        void ordinationSmartStack();

        // Funcions to process mergesort
        void mergeSort();
        void ordinationMerge(int left, int right);
        void merge(int left, int mid, int right);

        // Funcions to process heapsort
        void heapSort();
        void build();
        void remake(int left, int right);
        
    private:
        Register *regs;
        int N;

        int comparisons_qtd;
        int copies_qtd;
        double processing_time;

};
#endif