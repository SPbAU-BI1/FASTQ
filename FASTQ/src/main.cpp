#include "Archiver/LZ77/LZ77Archiver.h"
#include "Archiver/LZ78/LZ78Archiver.h"
#include "Archiver/FASTQ/FASTQArchiver.h"
#include "InputOutput/Buffered/BufferedReader.h"
#include "InputOutput/Buffered/BufferedWriter.h"
#include "InputOutput/StreamReader/StreamReader.h"
#include "Generator/Generator.h"

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
    FASTQArchiver *archiver = new FASTQArchiver();
    archiver->Compress(argv[1], argv[2]);
    //archiver->Decompress(argv[2], concatenate(argv[1], "_decompressed"));
}
