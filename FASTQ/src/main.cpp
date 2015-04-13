#include "LZ77/LZ77Archiver.h"
#include "LZ78/LZ78Archiver.h"
#include "IO/BufferReader.h"
#include "IO/BufferWriter.h"
#include "generator/Generator.h"

#include <stdlib.h>

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_RESET "\x1b[0m"

//FOR DEBUG
#include <bits/stdc++.h>
using namespace std;
//FOR DEBUG

int main(int argc, char **argv) {
    if (argc != 3) {
        printf(ANSI_COLOR_RED);
        printf("Error! You need to pass exactly 2 arguments: input and output files.\n");
        printf(ANSI_COLOR_RESET);
        exit(1);
    }

    const int length = 10000000;
    Generator *generator = new Generator();
    //be careful -- overwrites input file
    generator->run(argv[1], length);
	delete generator;
 

//    Archiver *archiver = new LZ77Archiver();
//    archiver->Compress(argv[1], argv[2]);
//    archiver->Decompress(argv[2], strcat(argv[1], "_decompressed"));


    int filename_length = strlen(argv[1]);
    char *filename_decompressed = new char[filename_length + strlen("_decompressed") + 1]();
    strcat(filename_decompressed, argv[1]);
    strcat(filename_decompressed, "_decompressed");
    Archiver *archiver = new LZ78Archiver();
    archiver->Compress(argv[1], argv[2]);
    archiver->Decompress(argv[2], filename_decompressed);
    delete filename_decompressed;


    delete archiver;
}
