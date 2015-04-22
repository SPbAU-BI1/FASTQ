#include "Archiver/LZ77/LZ77Archiver.h"
#include "Archiver/LZ78/LZ78Archiver.h"
#include "InputOutput/Buffered/BufferedReader.h"
#include "InputOutput/Buffered/BufferedWriter.h"
#include "Generator/Generator.h"
#include "InputOutput/StreamReader/StreamReader.h"

#include <stdlib.h>

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_RESET "\x1b[0m"

char* concatenate(const char *s1, const char *s2) {
    char *result = new char[strlen(s1) + strlen(s2) + 1]();
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

int main(int argc, char **argv) {
    if (argc != 3) {
        printf(ANSI_COLOR_RED);
        printf("Error! You need to pass exactly 2 arguments: input and output files.\n");
        printf(ANSI_COLOR_RESET);
        exit(1);
    }

    const int length = 100000;
    Generator *generator = new Generator();
    //be careful -- overwrites input file
    //generator->run(argv[1], length);
    delete generator;

    Archiver *archiver = new LZ78Archiver();
/*
    Writer *compress_writer = new BufferedWriter(argv[2]); 
    for (int i = 0; i < 4; i++)
    {
        Reader *compress_reader = new StreamReader(argv[1], 4, i);
        archiver->Compress(compress_reader, compress_writer);
        delete compress_reader; 
    }
*/

//    Reader *decompress_reader = new BufferedReader(argv[1]);
//    Writer *decompress_writer = new BufferedWriter(argv[2]);

//    archiver->Compress(decompress_reader, decompress_writer);

    Reader *decompress_reader = new BufferedReader(argv[1]);
    Writer *decompress_writer = new BufferedWriter(argv[2]);

    archiver->Decompress(decompress_reader, decompress_writer);

//    delete decompress_reader;

    /*
    char *filename_decompressed = concatenate(argv[1], "_decompressed");
    Reader *compress_reader = new BufferedReader(argv[1]);
    Writer *compress_writer = new BufferedWriter(argv[2]);
    archiver->Compress(compress_reader, compress_writer);
    delete compress_reader;
    delete compress_writer;
    
    Reader *decompress_reader = new BufferedReader(argv[2]);
    Writer *decompress_writer = new BufferedWriter(filename_decompressed);
    archiver->Decompress(decompress_reader, decompress_writer);
    delete decompress_reader;
    delete decompress_writer;
    delete filename_decompressed;
    */

    delete archiver;
}
