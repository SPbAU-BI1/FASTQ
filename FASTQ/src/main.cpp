#include "Archiver/LZ77/LZ77Archiver.h"
#include "Archiver/LZ78/LZ78Archiver.h"
#include "Archiver/FASTQ/FASTQArchiver.h"
#include "InputOutput/Buffered/BufferedReader.h"
#include "InputOutput/Buffered/BufferedWriter.h"
#include "InputOutput/Bit/BitReader.h"
#include "InputOutput/Bit/BitWriter.h"
#include "InputOutput/StreamReader/StreamReader.h"
#include "Generator/Generator.h"

#include <stdlib.h>
#include <iostream>

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

    FASTQArchiver *archiver = new FASTQArchiver();
    archiver->Compress(argv[1], argv[2]);
    archiver->Decompress(argv[2], concatenate(argv[1], "_decompressed"));
    
/*
    using std::cerr;
    using std::endl;
    Reader *compress_reader = new BufferedReader(argv[1]);
    Writer *compress_writer = new BufferedWriter(argv[2]);

    LZ78Archiver *archiver = new LZ78Archiver();
    std::cerr << "compressing. gonna write to: " << argv[2] << std::endl;
    archiver->Compress(compress_reader, compress_writer);

    delete compress_reader;
    delete compress_writer;

    Reader *decompress_reader = new BufferedReader(argv[2]);
    Writer *decompress_writer = new BufferedWriter(concatenate(argv[1], "_decompressed"));
    std::cerr << "gonna decompress: " << argv[2] << " to " << concatenate(argv[1], "_decompressed") << std::endl;
    archiver->Decompress(decompress_reader, decompress_writer);

    delete decompress_reader;
    delete decompress_writer;
*/
}
