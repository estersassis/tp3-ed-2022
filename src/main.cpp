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

    while ((c = getopt(argc, argv, "v:s:m:k:i:o:h")) != EOF)

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
            case 's':
                s = *optarg;
                break;
            case 'm':
                m = *optarg;
                break;
            case 'k':
                k = *optarg;
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
            {
                regs.quickSortRecursive();
                file << regs.getTotalTime() << std::endl;
            }
            case QSMEDIAN:
            {
                regs.quickSortMedian(k);
                file << regs.getTotalTime() << std::endl;
            }
            case QSSELECTION:
            {
                regs.quickSortSelection(m);
                file << regs.getTotalTime() << std::endl;
            }
            case QSINTERACTIVE:
            {
                regs.quickSortNonRecursive();
                file << regs.getTotalTime() << std::endl;
            }
            case QSINTERACTIVESMART:
            {
                regs.quickSortSmartStack();
                file << regs.getTotalTime() << std::endl;
            }
        }
    }

    file.close();
}