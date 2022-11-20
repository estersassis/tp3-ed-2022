#include "Registers.hpp"
#include "msgassert.h"
#include <iostream>
#include <getopt.h>
#include <string>
#include <fstream>
#include <sstream>
#include <memlog.h>

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
    double total_time;

    buffer >> running_count;

    std::ofstream file;
    file.open(outfilename);
    file << "N  TPT  CMN  CPN" << std::endl;

    for (int i = 0; i < running_count; i++)
    {
        buffer >> N;
        Registers regs(s, N);

        switch (opchoose)
        {
            case QUICKSORTREC:
                for (int i = 0; i < 5; i++)
                {
                    regs.quickSortRecursive();

                    total_comp += regs.getComparisonsQtd();
                    total_copy += regs.getCopiesQtd();
                    total_time += regs.getProcessingTime();

                    file << N << "  " << regs.getProcessingTime() << " " << regs.getComparisonsQtd() << " " << regs.getCopiesQtd() << std::endl;
                    
                    regs.restartMetrics();
                }
                break;

            case QUICKSORTMED:
                for (int i = 0; i < 5; i++)
                {
                    regs.quickSortMedian(k);

                    total_comp += regs.getComparisonsQtd();
                    total_copy += regs.getCopiesQtd();
                    total_time += regs.getProcessingTime();

                    file << N << "  " << regs.getProcessingTime() << " " << regs.getComparisonsQtd() << " " << regs.getCopiesQtd() << std::endl;

                    regs.restartMetrics();
                }
                break;
         
            case QUICKSORTSELECT:
                for (int i = 0; i < 5; i++)
                {
                    regs.quickSortSelection(m);

                    total_comp += regs.getComparisonsQtd();
                    total_copy += regs.getCopiesQtd();
                    total_time += regs.getProcessingTime();

                    file << N << "  " << regs.getProcessingTime() << " " << regs.getComparisonsQtd() << " " << regs.getCopiesQtd() << std::endl;

                    regs.restartMetrics();
                }
                break;
           
            case QUICKSORTITR:
                for (int i = 0; i < 5; i++)
                {
                    regs.quickSortNonRecursive();

                    total_comp += regs.getComparisonsQtd();
                    total_copy += regs.getCopiesQtd();
                    total_time += regs.getProcessingTime();

                    file << N << "  " << regs.getProcessingTime() << " " << regs.getComparisonsQtd() << " " << regs.getCopiesQtd() << std::endl;

                    regs.restartMetrics();
                }
                
                break;
        
            case QUICKSORTIRTSMART:
                for (int i = 0; i < 5; i++)
                {
                    regs.quickSortSmartStack();

                    total_comp += regs.getComparisonsQtd();
                    total_copy += regs.getCopiesQtd();
                    total_time += regs.getProcessingTime();

                    file << N << "  " << regs.getProcessingTime() << " " << regs.getComparisonsQtd() << " " << regs.getCopiesQtd() << std::endl;

                    regs.restartMetrics();
                }
                break;

            case MERGESORT:
                for (int i = 0; i < 5; i++)
                {
                    regs.mergeSort();

                    total_comp += regs.getComparisonsQtd();
                    total_copy += regs.getCopiesQtd();
                    total_time += regs.getProcessingTime();

                    file << N << "  " << regs.getProcessingTime() << " " << regs.getComparisonsQtd() << " " << regs.getCopiesQtd() << std::endl;

                    regs.restartMetrics();
                }
                break;
            
            case HEAPSORT:
                for (int i = 0; i < 5; i++)
                {
                    regs.heapSort();

                    total_comp += regs.getComparisonsQtd();
                    total_copy += regs.getCopiesQtd();
                    total_time += regs.getProcessingTime();

                    file << N << "  " << regs.getProcessingTime() << " " << regs.getComparisonsQtd() << " " << regs.getCopiesQtd() << std::endl;

                    regs.restartMetrics();
                }
                break;

            default:
                break;
        }
        file << "AVR  " << N << "  " << total_time / 5 << " " << total_comp / 5 << " " << total_copy / 5 << std::endl;
    }

    file.close();
}