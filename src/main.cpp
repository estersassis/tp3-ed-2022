#include "Registers.hpp"
#include "msgassert.h"
#include <iostream>
#include <getopt.h>
#include <string>
#include <fstream>
#include <sstream>
#include <memlog.h>
#include <sys/resource.h>
#include <iomanip>

#define QUICKSORTREC 1
#define QUICKSORTMED 2
#define QUICKSORTSELECT 3
#define QUICKSORTITR 4
#define QUICKSORTIRTSMART 5
#define MERGESORT 6
#define HEAPSORT 7

static int opchoose;
int regmem;
std::string inpfilename, outfilename, sorttechnique;
int N, m, k, s;

void use()
{
    std::cout << "Instructions:" << std::endl;
    std::cout << "Basic structure ----------------------------------------" << std::endl;
    std::cout << "<name of the sorting type> -v <version of sorting> -s <seed number> -i <input filename> -o <output filename>" << std::endl;
    std::cout << "Name of sorting types ----------------------------------------" << std::endl;
    std::cout << "- quicksort" << std::endl;
    std::cout << "- heapsort \t (only one version, -v 1)" << std::endl;
    std::cout << "- mergesort \t (only one version, -v 1)" << std::endl;
    std::cout << "Quicksort versions ----------------------------------------" << std::endl;
    std::cout << "- recursive: -v 1" << std::endl;
    std::cout << "- mediam: -v 2 -k <median of k elements>" << std::endl;
    std::cout << "- selective: -v 3 -m <when change to selection sort>" << std::endl;
    std::cout << "- interactive: -v 4" << std::endl;
    std::cout << "- smart interactive: -v 5" << std::endl;
}

void parseArgs(int argc, char **argv) {
    extern char *optarg;
    char sort_type;
    int c;

    opchoose = -1;
    regmem = 0;

    while ((c = getopt(argc, argv, "v:s:m:k:i:o:h")) != EOF){
        switch (c)
        {
            case 'v':
                sort_type = *optarg;
                if (sorttechnique == "quicksort") {
                    if (sort_type == '1')
                        opchoose = QUICKSORTREC;
                    else if(sort_type == '2')
                        opchoose = QUICKSORTMED;
                    else if (sort_type == '3')
                        opchoose = QUICKSORTSELECT;
                    else if (sort_type == '4')
                        opchoose = QUICKSORTITR;
                    else if (sort_type == '5')
                        opchoose = QUICKSORTIRTSMART;
                    else
                        erroAssert(0, "ERROR: QUICK SORT VERSION NOT FOUND");
                }
                else if (sorttechnique == "heapsort") {
                    if (sort_type == '1')
                        opchoose = HEAPSORT;
                }
                else if (sorttechnique == "mergesort") {
                    if (sort_type == '1')
                        opchoose = MERGESORT;
                }
                else
                    erroAssert(0, "ERROR: SORTING TYPE NOT FOUND");
                break;
            case 'k':
                k = atoi(optarg);
                break;
            case 's':
                s = atoi(optarg);
                break;
            case 'm':
                m = atoi(optarg);
                break;
            case 'i':
                inpfilename = optarg;
                break;
            case 'o':
                outfilename = optarg;
                break;
            case 'h':
                use();
                exit(1);
        }
    }
}

int main(int argc, char **argv)
{
    sorttechnique = argv[1];

    parseArgs(argc, argv);

    std::ifstream inpfile;
    inpfile.open(inpfilename);
    erroAssert(!inpfile.fail(), "ERROR: COULDN'T OPEN THE INPUT FILE");

    std::stringstream buffer;
    buffer << inpfile.rdbuf();

    inpfile.close();

    int running_count, total_comp, total_copy;
    double total_time, time;

    buffer >> running_count;

    std::ofstream file;
    file.open(outfilename);
    file << "N  TPT  CMN  CPN" << std::endl;

    struct rusage resources;
    double u_end, u_start, s_end, s_start;

    for (int i = 0; i < running_count; i++)
    {
        buffer >> N;

        switch (opchoose)
        {
            case QUICKSORTREC:
                for (int i = 0; i < 5; i++)
                {
                    Registers qsr(s, N);

                    getrusage(RUSAGE_SELF, &resources);
                    s_start = (double)resources.ru_stime.tv_sec + 1.e-6 * (double)resources.ru_stime.tv_usec;
                    u_start = (double)resources.ru_utime.tv_sec + 1.e-6 * (double)resources.ru_stime.tv_usec;

                    qsr.quickSortRecursive();

                    getrusage(RUSAGE_SELF, &resources);
                    s_end = (double)resources.ru_stime.tv_sec + 1.e-6 * (double)resources.ru_stime.tv_usec;
                    u_end = (double)resources.ru_utime.tv_sec + 1.e-6 * (double)resources.ru_stime.tv_usec;

                    total_comp += qsr.getComparisonsQtd();
                    total_copy += qsr.getCopiesQtd();
                    time = (s_end - s_start) + (u_end-u_start);
                    total_time += time;

                    file << std::fixed;
                    file << std::setprecision(6);
                    file << N << "  " << time << " " << qsr.getComparisonsQtd() << " " << qsr.getCopiesQtd() << std::endl;
                }
                break;

            case QUICKSORTMED:
                for (int i = 0; i < 5; i++)
                {
                    Registers qsm(s, N);

                    getrusage(RUSAGE_SELF, &resources);
                    s_start = (double)resources.ru_stime.tv_sec + 1.e-6 * (double)resources.ru_stime.tv_usec;
                    u_start = (double)resources.ru_utime.tv_sec + 1.e-6 * (double)resources.ru_stime.tv_usec;

                    qsm.quickSortMedian(k);

                    getrusage(RUSAGE_SELF, &resources);
                    s_end = (double)resources.ru_stime.tv_sec + 1.e-6 * (double)resources.ru_stime.tv_usec;
                    u_end = (double)resources.ru_utime.tv_sec + 1.e-6 * (double)resources.ru_stime.tv_usec;
                    

                    total_comp += qsm.getComparisonsQtd();
                    total_copy += qsm.getCopiesQtd();
                    time = (s_end - s_start) + (u_end - u_start);
                    total_time += time;

                    file << std::fixed;
                    file << std::setprecision(6);
                    file << N << "  " << time << " " << qsm.getComparisonsQtd() << " " << qsm.getCopiesQtd() << std::endl;
                }
                break;
         
            case QUICKSORTSELECT:
                for (int i = 0; i < 5; i++)
                {
                    Registers qss(s, N);

                    getrusage(RUSAGE_SELF, &resources);
                    s_start = (double)resources.ru_stime.tv_sec + 1.e-6 * (double)resources.ru_stime.tv_usec;
                    u_start = (double)resources.ru_utime.tv_sec + 1.e-6 * (double)resources.ru_stime.tv_usec;

                    qss.quickSortSelection(m);

                    getrusage(RUSAGE_SELF, &resources);
                    s_end = (double)resources.ru_stime.tv_sec + 1.e-6 * (double)resources.ru_stime.tv_usec;
                    u_end = (double)resources.ru_utime.tv_sec + 1.e-6 * (double)resources.ru_stime.tv_usec;
                    

                    total_comp += qss.getComparisonsQtd();
                    total_copy += qss.getCopiesQtd();
                    time = (s_end - s_start) + (u_end - u_start);
                    total_time += time;

                    file << std::fixed;
                    file << std::setprecision(6);
                    file << N << "  " << time << " " << qss.getComparisonsQtd() << " " << qss.getCopiesQtd() << std::endl;
                }
                break;
           
            case QUICKSORTITR:
                for (int i = 0; i < 5; i++)
                {
                    Registers qsi(s, N);
                    
                    getrusage(RUSAGE_SELF, &resources);
                    s_start = (double)resources.ru_stime.tv_sec + 1.e-6 * (double)resources.ru_stime.tv_usec;
                    u_start = (double)resources.ru_utime.tv_sec + 1.e-6 * (double)resources.ru_stime.tv_usec;

                    qsi.quickSortNonRecursive();

                    getrusage(RUSAGE_SELF, &resources);
                    s_end = (double)resources.ru_stime.tv_sec + 1.e-6 * (double)resources.ru_stime.tv_usec;
                    u_end = (double)resources.ru_utime.tv_sec + 1.e-6 * (double)resources.ru_stime.tv_usec;

                    total_comp += qsi.getComparisonsQtd();
                    total_copy += qsi.getCopiesQtd();
                    time = (s_end - s_start) + (u_end - u_start);
                    total_time += time;

                    file << std::fixed;
                    file << std::setprecision(6);
                    file << N << "  " << time << " " << qsi.getComparisonsQtd() << " " << qsi.getCopiesQtd() << std::endl;
                }
                
                break;
        
            case QUICKSORTIRTSMART:
                for (int i = 0; i < 5; i++)
                {
                    Registers qsis(s, N);

                    getrusage(RUSAGE_SELF, &resources);
                    s_start = (double)resources.ru_stime.tv_sec + 1.e-6 * (double)resources.ru_stime.tv_usec;
                    u_start = (double)resources.ru_utime.tv_sec + 1.e-6 * (double)resources.ru_stime.tv_usec;

                    qsis.quickSortSmartStack();

                    getrusage(RUSAGE_SELF, &resources);
                    s_end = (double)resources.ru_stime.tv_sec + 1.e-6 * (double)resources.ru_stime.tv_usec;
                    u_end = (double)resources.ru_utime.tv_sec + 1.e-6 * (double)resources.ru_stime.tv_usec;

                    total_comp += qsis.getComparisonsQtd();
                    total_copy += qsis.getCopiesQtd();
                    time = (s_end - s_start) + (u_end - u_start);
                    total_time += time;

                    file << std::fixed;
                    file << std::setprecision(6);
                    file << N << "  " << time << " " << qsis.getComparisonsQtd() << " " << qsis.getCopiesQtd() << std::endl;
                }
                break;

            case MERGESORT:
                for (int i = 0; i < 5; i++)
                {
                    Registers ms(s, N);

                    getrusage(RUSAGE_SELF, &resources);
                    s_start = (double)resources.ru_stime.tv_sec + 1.e-6 * (double)resources.ru_stime.tv_usec;
                    u_start = (double)resources.ru_utime.tv_sec + 1.e-6 * (double)resources.ru_stime.tv_usec;

                    ms.mergeSort();

                    getrusage(RUSAGE_SELF, &resources);
                    s_end = (double)resources.ru_stime.tv_sec + 1.e-6 * (double)resources.ru_stime.tv_usec;
                    u_end = (double)resources.ru_utime.tv_sec + 1.e-6 * (double)resources.ru_stime.tv_usec;

                    total_comp += ms.getComparisonsQtd();
                    total_copy += ms.getCopiesQtd();
                    time = (s_end - s_start) + (u_end - u_start);
                    total_time += time;

                    file << std::fixed;
                    file << std::setprecision(6);
                    file << N << "  " << time << " " << ms.getComparisonsQtd() << " " << ms.getCopiesQtd() << std::endl;
                }
                break;
            
            case HEAPSORT:
                for (int i = 0; i < 5; i++)
                {
                    Registers hs(s, N);

                    s_start = (double)resources.ru_stime.tv_sec + 1.e-6 * (double)resources.ru_stime.tv_usec;
                    u_start = (double)resources.ru_utime.tv_sec + 1.e-6 * (double)resources.ru_stime.tv_usec;
                    
                    hs.heapSort();

                    getrusage(RUSAGE_SELF, &resources);
                    s_end = (double)resources.ru_stime.tv_sec + 1.e-6 * (double)resources.ru_stime.tv_usec;
                    u_end = (double)resources.ru_utime.tv_sec + 1.e-6 * (double)resources.ru_stime.tv_usec;

                    total_comp += hs.getComparisonsQtd();
                    total_copy += hs.getCopiesQtd();
                    time = (s_end - s_start) + (u_end - u_start);
                    total_time += time;

                    file << std::fixed;
                    file << std::setprecision(6);
                    file << N << "  " << time << " " << hs.getComparisonsQtd() << " " << hs.getCopiesQtd() << std::endl;
                }
                break;

            default:
                break;
        }
        file << std::fixed;
        file << std::setprecision(6);
        file << "AVR  " << N << "  " << total_time / 5 << " " << total_comp / 5 << " " << total_copy / 5 << std::endl;
        total_comp = 0;
        total_copy = 0;
        total_time = 0.0;
    }
    file.close();
}