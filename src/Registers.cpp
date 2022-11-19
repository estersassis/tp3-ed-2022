#include "Registers.hpp"
#include <iostream>
#include <stdio.h>
#include <sys/resource.h>


Registers::Registers(int seed, int N) {
    this->N = N;
    this->compValue = 0;
    this->copyValue = 0;
    this->regs = new Register[N];

    srand(seed);
    for (int i = 0; i < N; i++) {
        int random = rand();
        this->regs[i] = Register(random);
    }
}

Registers::~Registers(){}

// QUICK SORT RECURSSIVO

double Registers::getTotalTime(){
    return this->totalTime;
}

void Registers::partitionRecursive(int left, int right, int *i, int *j) {

    Register x, w;
    *i = left; *j = right;

    x = this->regs[(*i + *j)/2];

    do
    {
        while (x.getKey() > this->regs[*i].getKey())
            (*i)++;
        while (x.getKey() < this->regs[*j].getKey())
            (*j)--;

        if (*i <= *j) {
            w = this->regs[*i];
            this->regs[*i] = this->regs[*j];
            this->regs[*j] = w;
            (*i)++;
            (*j)--;
        }
    } while (*i <= *j);
}

void Registers::ordinationRecursive(int left, int right)
{
    int i, j;

    this->partitionRecursive(left, right, &i, &j);
    if (left < j)
        this->ordinationRecursive(left, j);
    if (i < right)
        this->ordinationRecursive(i, right);
}

void Registers::quickSortRecursive() {
    struct rusage resources;
    int rc;
    double utime, stime;

    this->ordinationRecursive(0, this->N - 1);

    if ((rc = getrusage(RUSAGE_SELF, &resources)) != 0)
        perror("getrusage failed");
    utime = (double)resources.ru_utime.tv_sec + 1.e-6 * (double)resources.ru_utime.tv_usec;
    stime = (double)resources.ru_stime.tv_sec + 1.e-6 * (double)resources.ru_stime.tv_usec;

    this->totalTime = utime + stime;
}

// QUICK SORT MEDIANA K

int Registers::chooseRandonMedian(int k, int left, int right)
{
    int aux[k];

    for (int i = 0; i < k; i++)
    {
        aux[i] = this->regs[left + (rand() % right)].getKey();
    }

    for (int i = 0; i < k - 1; i++)
        for (int j = 1; j < k - i; j++)
            if (aux[j] < aux[j - 1])
            {
                int ch = aux[j - 1];
                aux[j - 1] = aux[j];
                aux[j] = ch;
            }

    return aux[k / 2];
}

void Registers::partitionMedian(int left, int right, int *i, int *j, int k)
{

    Register w;
    int x;
    *i = left;
    *j = right;

    x = this->chooseRandonMedian(k, left, right);

    do
    {
        while (x > this->regs[*i].getKey())
            (*i)++;
        while (x < this->regs[*j].getKey())
            (*j)--;

        if (*i <= *j)
        {
            w = this->regs[*i];
            this->regs[*i] = this->regs[*j];
            this->regs[*j] = w;
            (*i)++;
            (*j)--;
        }
    } while (*i <= *j);
}

void Registers::ordinationMedian(int left, int right, int k)
{
    int i, j;

    this->partitionMedian(left, right, &i, &j, k);
    if (left < j)
        this->ordinationMedian(left, j, k);
    if (i < right)
        this->ordinationMedian(i, right, k);
}

void Registers::quickSortMedian(int k)
{
    struct rusage resources;
    int rc;
    double utime, stime;

    this->ordinationMedian(0, this->N - 1, k);

    if ((rc = getrusage(RUSAGE_SELF, &resources)) != 0)
        perror("getrusage failed");
    utime = (double)resources.ru_utime.tv_sec + 1.e-6 * (double)resources.ru_utime.tv_usec;
    stime = (double)resources.ru_stime.tv_sec + 1.e-6 * (double)resources.ru_stime.tv_usec;

    this->totalTime = utime + stime;
}

// QUICK SORT SELECAO

void Registers::selectSort(int left, int right) {
    int i, j, Min;
    int n = right + 1;

    for (i = left; i < n - 1; i++) {
        Min = i;
        for (j = i + 1; j < n; j++) {
            if (this->regs[j].getKey() < this->regs[Min].getKey())
                Min = j;
        }

        Register aux = this->regs[i];
        this->regs[i] = this->regs[Min];
        this->regs[Min] = aux;
    }
}

void Registers::ordinationSelection(int left, int right, int m) {
    int i, j;

    if (right - left + 1 == m) {
        this->selectSort(left, right);
    }
    else {
        this->partitionRecursive(left, right, &i, &j);
        if (left < j)
            this->ordinationSelection(left, j, m);
        if (i < right)
            this->ordinationSelection(i, right, m);
    }
}

void Registers::quickSortSelection(int m) {
    struct rusage resources;
    int rc;
    double utime, stime;

    this->ordinationSelection(0, this->N - 1, m);

    if ((rc = getrusage(RUSAGE_SELF, &resources)) != 0)
        perror("getrusage failed");
    utime = (double)resources.ru_utime.tv_sec + 1.e-6 * (double)resources.ru_utime.tv_usec;
    stime = (double)resources.ru_stime.tv_sec + 1.e-6 * (double)resources.ru_stime.tv_usec;

    this->totalTime = utime + stime;
}

// QUICK SORT NON RECURSIVE
class Item {
    public:
        int left = -1, right = -1;
};

class Stack {
    public: 
        Item *stack;
        int size = 0;

        Stack(int k) {
            stack = new Item[k];
            size = 0;
        };
        
        void Empilha (Item item) {
            stack[size] = item;
            size++;
        }

        void Desempilha () {
            size--;
        }
        ~Stack() { delete stack; };
};

void Registers::ordinationSmartStack()
{
    Stack stack(N);
    Item item;

    int left, right, i, j;

    left = 0;
    right = N - 1;
    item.left = left;
    item.right = right;

    stack.Empilha(item);

    do
        if (right > left)
        {
            this->partitionRecursive(left, right, &i, &j);
            if ((j - left) > (right - i))
            {
                item.right = j;
                item.left = left;
                stack.Empilha(item);
                left = i;
            }
            else
            {
                item.left = i;
                item.right = right;
                stack.Empilha(item);
                right = j;
            }
        }
        else
        {
            stack.Desempilha();
            right = item.right;
            left = item.left;
        }
    while (stack.size != 0);
}

void Registers::quickSortSmartStack()
{
    struct rusage resources;
    int rc;
    double utime, stime;

    this->ordinationSmartStack();

    if ((rc = getrusage(RUSAGE_SELF, &resources)) != 0)
        perror("getrusage failed");
    utime = (double)resources.ru_utime.tv_sec + 1.e-6 * (double)resources.ru_utime.tv_usec;
    stime = (double)resources.ru_stime.tv_sec + 1.e-6 * (double)resources.ru_stime.tv_usec;

    this->totalTime = utime + stime;
}

void Registers::ordinationNonRecursive()
{
    Stack stack(N);
    Item item;

    int left, right, i, j;

    left = 0;
    right = N - 1;
    item.left = left;
    item.right = right;

    stack.Empilha(item);

    do
        if (right > left)
        {
            this->partitionRecursive(left, right, &i, &j);
            if ((j - left) < (right - i))
            {
                item.right = j;
                item.left = left;
                stack.Empilha(item);
                left = i;
            }
            else
            {
                item.left = i;
                item.right = right;
                stack.Empilha(item);
                right = j;
            }
        }
        else
        {
            stack.Desempilha();
            right = item.right;
            left = item.left;
        }
    while (stack.size != 0);
}

void Registers::quickSortNonRecursive()
{
    struct rusage resources;
    int rc;
    double utime, stime;

    this->ordinationNonRecursive();

    if ((rc = getrusage(RUSAGE_SELF, &resources)) != 0)
        perror("getrusage failed");
    utime = (double)resources.ru_utime.tv_sec + 1.e-6 * (double)resources.ru_utime.tv_usec;
    stime = (double)resources.ru_stime.tv_sec + 1.e-6 * (double)resources.ru_stime.tv_usec;

    this->totalTime = utime + stime;
}

// HEAP SORT
void Registers::remake(int left, int right)
{
    int i, j;
    Register x;
    i = left;
    j = i * 2;
    x = this->regs[i];
    while (j <= right)
    {
        if (j < right)
            if (this->regs[j].getKey() < this->regs[j + 1].getKey())
                j++;
        if (x.getKey() >= this->regs[j].getKey())
            break;
        this->regs[i] = this->regs[j];
        i = j;
        j = i * 2;
    }
    this->regs[i] = x;
}

void Registers::build()
{
    int left;
    left = N / 2 + 1;
    while (left > 0)
    {
        left--;
        remake(left, N);
    }
}

void Registers::heapSort()
{
    struct rusage resources;
    int rc;
    double utime, stime;

    int left, right;
    Register x;

    build();

    left = 0;
    right = N - 1;

    while (right > 0)
    {
        x = this->regs[0];
        this->regs[0] = this->regs[right];
        this->regs[right] = x;
        right--;
        remake(left, right);
    }

    if ((rc = getrusage(RUSAGE_SELF, &resources)) != 0)
        perror("getrusage failed");
    utime = (double)resources.ru_utime.tv_sec + 1.e-6 * (double)resources.ru_utime.tv_usec;
    stime = (double)resources.ru_stime.tv_sec + 1.e-6 * (double)resources.ru_stime.tv_usec;

    this->totalTime = utime + stime;
}

void Registers::merge(int left, int mid, int right)
{
    auto const subArrayOne = mid - left + 1;
    auto const subArrayTwo = right - mid;

    auto *leftArray = new Register[subArrayOne],
         *rightArray = new Register[subArrayTwo];

    for (auto i = 0; i < subArrayOne; i++)
        leftArray[i] = this->regs[left + i].getKey();
    for (auto j = 0; j < subArrayTwo; j++)
        rightArray[j] = this->regs[mid + 1 + j].getKey();

    auto indexOfSubArrayOne = 0,   
        indexOfSubArrayTwo = 0;  
    int indexOfMergedArray = left; 

    while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo)
    {
        if (leftArray[indexOfSubArrayOne].getKey() <= rightArray[indexOfSubArrayTwo].getKey())
        {
            this->regs[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
        }
        else
        {
            this->regs[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
    }
    
    while (indexOfSubArrayOne < subArrayOne)
    {
        this->regs[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }
    
    while (indexOfSubArrayTwo < subArrayTwo)
    {
        this->regs[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }
    delete[] leftArray;
    delete[] rightArray;
}

void Registers::ordinationMerge(int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        ordinationMerge(left, mid);
        ordinationMerge(mid + 1, right);
        merge(left, mid, right);
    }
}

void Registers::mergeSort()
{
    struct rusage resources;
    int rc;
    double utime, stime;

    this->ordinationMerge(0, N - 1);

    if ((rc = getrusage(RUSAGE_SELF, &resources)) != 0)
        perror("getrusage failed");
    utime = (double)resources.ru_utime.tv_sec + 1.e-6 * (double)resources.ru_utime.tv_usec;
    stime = (double)resources.ru_stime.tv_sec + 1.e-6 * (double)resources.ru_stime.tv_usec;

    this->totalTime = utime + stime;

}