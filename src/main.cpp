#include <iostream>
#include <getopt.h>
#include <string>
#include <fstream>
#include <sstream>
#include <memlog.h>
#include <sys/resource.h>
#include <iomanip>
#include "msgassert.h"
#include "DicionarioHash.hpp"
#include "DicionarioAVL.hpp"

#define HASH 1
#define AVL 2

static int opchoose;
int regmem;
std::string inpfilename, outfilename;

void parseArgs(int argc, char **argv)
{
    extern char *optarg;
    std::string s;
    int c;

    opchoose = -1;
    regmem = 0;

    while ((c = getopt(argc, argv, "i:o:t:hl")) != EOF)
    {
        switch (c)
        {
            case 't':
                s = optarg;
                if (s == "hash") 
                    opchoose = HASH;
                else if(s == "arv")
                    opchoose = AVL;
                break;
            case 'i':
                inpfilename = optarg;
                break;
            case 'o':
                outfilename = optarg;
                break;
            case 'l':
                regmem = 1;
                break;
            case 'h':
                exit(1);
        }
    }
}

int main(int argc, char **argv)
{
    parseArgs(argc, argv);

    std::ifstream inpfile;
    std::ofstream outfile;

    inpfile.open(inpfilename);
    erroAssert(!inpfile.fail(), "ERROR: COULDN'T OPEN THE INPUT FILE");

    char tipo;
    std::string verb;
    std::string meaning;
    std::string line;
    int number_of_lines = 0;

    while (std::getline(inpfile, line))
        ++number_of_lines;

    inpfile.clear();
    inpfile.seekg(0, inpfile.beg);

    DicionarioHash hash(number_of_lines);
    DicionarioAVL avl(number_of_lines);

    switch (opchoose)
    {
        case HASH:

            while (std::getline(inpfile, line))
            {
                Verbete aux(number_of_lines);
                Significado aux_s;

                tipo = line[0];
                verb = line.substr(2, line.find("]"));
                verb = verb.substr(verb.find("[") + 1, verb.find("]")-1);
                
                meaning = line.substr(line.find("]") + 1, std::string::npos);
                meaning = meaning.substr(meaning.find(" ") + 1, std::string::npos);

                aux.setVerbete(verb);
                aux.setTipo(tipo);
                if (meaning != "")
                {
                    aux_s.setText(meaning);
                    aux.insertSiginificado(aux_s);
                }

                hash.insere(aux);
                
            }
            inpfile.close();

            outfile.open(outfilename);
            erroAssert(!outfile.fail(), "ERROR: COULDN'T OPEN THE INPUT FILE");

            hash.imprimeDic(outfile);
            hash.removeDic();
            hash.imprimeDic(outfile);

            outfile.close();
            break;
        
        case AVL:

            while (std::getline(inpfile, line))
            {
                Verbete aux(number_of_lines);
                Significado aux_s;

                tipo = line[0];
                verb = line.substr(2, line.find("]"));
                verb = verb.substr(verb.find("[") + 1, verb.find("]") - 1);

                meaning = line.substr(line.find("]") + 1, std::string::npos);
                meaning = meaning.substr(meaning.find(" ") + 1, std::string::npos);

                aux.setVerbete(verb);
                aux.setTipo(tipo);
                if (meaning != "")
                {
                    aux_s.setText(meaning);
                    aux.insertSiginificado(aux_s);
                }

                avl.insere(aux);
            }
            inpfile.close();

            outfile.open(outfilename);
            erroAssert(!outfile.fail(), "ERROR: COULDN'T OPEN THE INPUT FILE");

            avl.imprimeDic(outfile);
            avl.removeDic();
            avl.imprimeDic(outfile);

            outfile.close();
            break;
    }
}