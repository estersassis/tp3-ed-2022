#include "Registers.hpp"
#include <iostream>
#include <getopt.h>
#include <string>
#include <fstream>
#include <sstream>

#define QSRECURSIVE 1
#define QSMEDIAN 2
#define QSSELECTION 3
#define QSINTERACTIVE 4
#define QSINTERACTIVESMART 5
#define MS 6
#define HS 7

static int opchoose;
int regmem;
std::string inpfilename, outfilename;
int N, m, k, s;

void parse_args(int argc, char **argv)
{
    extern char *optarg;
    char a;

    int c;

    opchoose = -1;
    regmem = 0;

    while ((c = getopt(argc, argv, "a:b:v:s:m:k:i:o:h")) != EOF){
        switch (c)
        {
            case 'v':
                a = *optarg;
                if (a == '1')
                    opchoose = QSRECURSIVE;
                else if(a == '2')
                    opchoose = QSMEDIAN;
                else if (a == '3')
                    opchoose = QSSELECTION;
                else if (a == '4')
                    opchoose = QSINTERACTIVE;
                else if (a == '5')
                    opchoose = QSINTERACTIVESMART;
                break;
            case 'b':
                a = *optarg;
                if (a == '1')
                    opchoose = MS;
            case 'a':
                a = *optarg;
                if (a == '1')
                    opchoose = HS;
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
                exit(1);
        }
    }
}

int main(int argc, char **argv)
{
   
    parse_args(argc, argv);

    std::ifstream inpfile;
    inpfile.open(inpfilename);
    std::stringstream buffer;
    buffer << inpfile.rdbuf();
    inpfile.close();

    int count;

    buffer >> count;

    std::ofstream file;
    file.open(outfilename);

    for (int i = 0; i < count; i++)
    {
        buffer >> N;
        Registers regs(s, N);

        switch (opchoose)
        {
            case QSRECURSIVE:
                regs.quickSortRecursive();
                break;

            case QSMEDIAN:
                regs.quickSortMedian(k);
                break;
         
            case QSSELECTION:
                regs.quickSortSelection(m);
                break;
           
            case QSINTERACTIVE:
                regs.quickSortNonRecursive();
                break;
           
            case QSINTERACTIVESMART:
                regs.quickSortSmartStack();
                break;

            case MS:
                regs.mergeSort();
                break;
            
            case HS:
                regs.heapSort();
                break;

            default:
                break;
        }
        file << regs.getMetrics() << std::endl;
    }

    file.close();
}