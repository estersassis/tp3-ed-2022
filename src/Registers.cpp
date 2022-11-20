#include "Registers.hpp"
#include "Stack.cpp"
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <sys/resource.h>


Registers::Registers(int seed, int N) {
    this->N = N;
    this->comparisons_qtd = 0;
    this->copies_qtd = 0;
    this->processing_time = 0.0;
    this->regs = new Register[N];

    // Generates the random keys for each register
    srand(seed);
    for (int i = 0; i < N; i++) {
        int random = rand();
        this->regs[i] = Register(random);
    }
}

Registers::~Registers() { delete[] this->regs; }

// METRICS ACCESS

double Registers::getProcessingTime() { return this->processing_time; }

int Registers::getComparisonsQtd() { return this->comparisons_qtd; }

int Registers::getCopiesQtd() { return this->copies_qtd; }

void Registers::restartMetrics() {
    this->processing_time = 0.0;
    this->comparisons_qtd = 0;
    this->copies_qtd = 0;
}

// BASIC PARTITION FUNCTION

void Registers::partiton(int left, int right, int *i, int *j) {

    Register x, w;
    *i = left; *j = right;

    x = this->regs[(*i + *j)/2];

    do {
        while (x.getKey() > this->regs[*i].getKey()) {
            (*i)++;
            this->comparisons_qtd++;
        }

        while (x.getKey() < this->regs[*j].getKey()) {
            (*j)--;
            this->comparisons_qtd++;
        }

        if (*i <= *j) {
            w = this->regs[*i];
            this->regs[*i] = this->regs[*j];
            this->regs[*j] = w;
            this->copies_qtd++;
            (*i)++;
            (*j)--;
        }
    } while (*i <= *j);
}

// PATTERN RECURSIVE QUICK SORT

void Registers::ordinationRecursive(int left, int right) {
    int i, j;

    this->partiton(left, right, &i, &j);
    if (left < j) {
        this->comparisons_qtd++;
        this->ordinationRecursive(left, j);
    }
    if (i < right) {
        this->comparisons_qtd++;
        this->ordinationRecursive(i, right);
    }
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

    this->processing_time = utime + stime;
}

// MEDIAM RECURSIVE QUICK SORT

int Registers::chooseRandonMedian(int k, int left, int right) {
    int aux[k];

    for (int i = 0; i < k; i++) {
        aux[i] = this->regs[left + (rand() % (right-left+1))].getKey();
    }

    for (int i = 0; i < k - 1; i++)
        for (int j = 1; j < k - i; j++)
            if (aux[j] < aux[j - 1]) {
                this->comparisons_qtd++;
                this->copies_qtd++;
                int ch = aux[j - 1];
                aux[j - 1] = aux[j];
                aux[j] = ch;
            }

    return aux[k / 2];
}

void Registers::partitionMedian(int left, int right, int *i, int *j, int k) {
    Register w;
    int x;
    *i = left;
    *j = right;

    x = this->chooseRandonMedian(k, left, right);

    do {
        while (x > this->regs[*i].getKey()) {
            (*i)++;
            this->comparisons_qtd++;
        }
            
        while (x < this->regs[*j].getKey()) {
            (*j)--;
            this->comparisons_qtd++;
        }

        if (*i <= *j) {
            w = this->regs[*i];
            this->regs[*i] = this->regs[*j];
            this->regs[*j] = w;
            this->copies_qtd++;
            (*i)++;
            (*j)--;
        }
    } while (*i <= *j);
}

void Registers::ordinationMedian(int left, int right, int k) {
    int i, j;

    this->partitionMedian(left, right, &i, &j, k);
    if (left < j) {
        this->comparisons_qtd++;
        this->ordinationMedian(left, j, k);
    }
    if (i < right) {
        this->comparisons_qtd++;
        this->ordinationMedian(i, right, k);
    }
}

void Registers::quickSortMedian(int k) {
    struct rusage resources;
    int rc;
    double utime, stime;

    this->ordinationMedian(0, this->N - 1, k);

    if ((rc = getrusage(RUSAGE_SELF, &resources)) != 0)
        perror("getrusage failed");

    utime = (double)resources.ru_utime.tv_sec + 1.e-6 * (double)resources.ru_utime.tv_usec;
    stime = (double)resources.ru_stime.tv_sec + 1.e-6 * (double)resources.ru_stime.tv_usec;

    this->processing_time = utime + stime;
}

// SELECTION RECURSIVE QUICK SORT

void Registers::selectSort(int left, int right) {
    int i, j, Min;
    int n = right + 1;

    for (i = left; i < n - 1; i++) {
        Min = i;
        for (j = i + 1; j < n; j++) {
            if (this->regs[j].getKey() < this->regs[Min].getKey()) {
                this->comparisons_qtd++;
                this->copies_qtd++;
                Min = j;
            }
        }

        Register aux = this->regs[i];
        this->regs[i] = this->regs[Min];
        this->regs[Min] = aux;
        this->copies_qtd++;
    }
}

void Registers::ordinationSelection(int left, int right, int m) {
    int i, j;

    if (right - left + 1 == m) {
        this->comparisons_qtd++;
        this->selectSort(left, right);
    }
    else {
        this->partiton(left, right, &i, &j);

        if (left < j) {
            this->comparisons_qtd++;
            this->ordinationSelection(left, j, m);
        }
        if (i < right) {
            this->comparisons_qtd++;
            this->ordinationSelection(i, right, m);
        }
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

    this->processing_time = utime + stime;
}

// NON RECURSIVE/INTERACTIVE QUICK SORT - Using biggest side

void Registers::ordinationNonRecursive() {
    Stack stack(N);
    Item item;

    int left, right, i, j;

    left = 0;
    right = N - 1;
    item.left = left;
    item.right = right;

    stack.Empilha(item);

    do
        if (right > left) {
            this->comparisons_qtd++;
            this->partiton(left, right, &i, &j);
            if ((j - left) < (right - i)) {
                this->comparisons_qtd++;
                item.right = j;
                item.left = left;
                stack.Empilha(item);
                left = i;
                this->copies_qtd++;
            }
            else {
                this->comparisons_qtd++;
                item.left = i;
                item.right = right;
                stack.Empilha(item);
                right = j;
                this->copies_qtd++;
            }
        }
        else {
            this->comparisons_qtd++;
            stack.Desempilha();
            right = item.right;
            left = item.left;
            this->copies_qtd++;
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

    this->processing_time = utime + stime;
}

// NON RECURSIVE/INTERACTIVE SMART QUICK SORT - Using shortest side

void Registers::ordinationSmartStack() {
    Stack stack(N);
    Item item;

    int left, right, i, j;

    left = 0;
    right = N - 1;
    item.left = left;
    item.right = right;

    stack.Empilha(item);

    do
        if (right > left) {
            this->comparisons_qtd++;
            this->partiton(left, right, &i, &j);
            if ((j - left) > (right - i)) {
                this->comparisons_qtd++;
                item.right = j;
                item.left = left;
                stack.Empilha(item);
                left = i;
                this->copies_qtd++;
            }
            else {
                this->comparisons_qtd++;
                item.left = i;
                item.right = right;
                stack.Empilha(item);
                right = j;
                this->copies_qtd++;
            }
        }
        else {
            this->comparisons_qtd++;
            stack.Desempilha();
            right = item.right;
            left = item.left;
            this->copies_qtd++;
        }
    while (stack.size != 0);
}

void Registers::quickSortSmartStack() {
    struct rusage resources;
    int rc;
    double utime, stime;

    this->ordinationSmartStack();

    if ((rc = getrusage(RUSAGE_SELF, &resources)) != 0)
        perror("getrusage failed");

    utime = (double)resources.ru_utime.tv_sec + 1.e-6 * (double)resources.ru_utime.tv_usec;
    stime = (double)resources.ru_stime.tv_sec + 1.e-6 * (double)resources.ru_stime.tv_usec;

    this->processing_time = utime + stime;
}

// HEAP SORT

void Registers::remake(int left, int right) {
    int i, j;
    Register x;
    i = left;
    j = i * 2;
    x = this->regs[i];

    while (j <= right) {
        if (j < right)
            if (this->regs[j].getKey() < this->regs[j + 1].getKey()) {
                this->comparisons_qtd++;
                j++;
            }
        if (x.getKey() >= this->regs[j].getKey()) {
            this->comparisons_qtd++;
            break;
        }
        this->regs[i] = this->regs[j];
        i = j;
        j = i * 2;
        this->copies_qtd++;
    }
    this->regs[i] = x;
}

void Registers::build() {
    int left;
    left = N / 2 + 1;
    while (left > 0) {
        left--;
        remake(left, N);
    }
}

void Registers::heapSort() {
    struct rusage resources;
    int rc;
    double utime, stime;

    int left, right;
    Register x;

    build();

    left = 0;
    right = N - 1;

    while (right > 0) {
        x = this->regs[0];
        this->regs[0] = this->regs[right];
        this->regs[right] = x;
        right--;
        remake(left, right);
        this->copies_qtd++;
    }

    if ((rc = getrusage(RUSAGE_SELF, &resources)) != 0)
        perror("getrusage failed");

    utime = (double)resources.ru_utime.tv_sec + 1.e-6 * (double)resources.ru_utime.tv_usec;
    stime = (double)resources.ru_stime.tv_sec + 1.e-6 * (double)resources.ru_stime.tv_usec;

    this->processing_time = utime + stime;
}

// MERGE SORT

void Registers::merge(int left, int mid, int right) {
    
    auto const partition_one = mid - left + 1;
    auto const partition_two = right - mid;

    auto *left_partition = new Register[partition_one],
         *right_partition = new Register[partition_two];

    for (auto i = 0; i < partition_one; i++) {
        left_partition[i] = this->regs[left + i].getKey();
        this->copies_qtd++;
    }

    for (auto j = 0; j < partition_two; j++) {
        right_partition[j] = this->regs[mid + 1 + j].getKey();
        this->copies_qtd++;
    }

    auto partition_one_idx = 0,   
        partition_two_idx = 0;  
    int merged_idx = left; 

    while (partition_one_idx < partition_one && partition_two_idx < partition_two) {
        if (left_partition[partition_one_idx].getKey() <= right_partition[partition_two_idx].getKey()) {
            this->comparisons_qtd++;
            this->regs[merged_idx] = left_partition[partition_one_idx];
            this->copies_qtd++;

            partition_one_idx++;
        }
        else {
            this->comparisons_qtd++;
            this->regs[merged_idx] = right_partition[partition_two_idx];
            this->copies_qtd++;

            partition_two_idx++;
        }
        merged_idx++;
    }
    
    while (partition_one_idx < partition_one) {
        this->regs[merged_idx] = left_partition[partition_one_idx];
        this->copies_qtd++;

        partition_one_idx++;
        merged_idx++;
    }
    
    while (partition_two_idx < partition_two) {
        this->regs[merged_idx] = right_partition[partition_two_idx];
        this->copies_qtd++;

        partition_two_idx++;
        merged_idx++;
    }
    delete[] left_partition;
    delete[] right_partition;
}

void Registers::ordinationMerge(int left, int right) {
    if (left < right) {
        this->comparisons_qtd++;

        int mid = left + (right - left) / 2;

        ordinationMerge(left, mid);
        ordinationMerge(mid + 1, right);

        merge(left, mid, right);
    }
}

void Registers::mergeSort() {
    struct rusage resources;
    int rc;
    double utime, stime;

    this->ordinationMerge(0, N - 1);

    if ((rc = getrusage(RUSAGE_SELF, &resources)) != 0)
        perror("getrusage failed");

    utime = (double)resources.ru_utime.tv_sec + 1.e-6 * (double)resources.ru_utime.tv_usec;
    stime = (double)resources.ru_stime.tv_sec + 1.e-6 * (double)resources.ru_stime.tv_usec;

    this->processing_time = utime + stime;
}