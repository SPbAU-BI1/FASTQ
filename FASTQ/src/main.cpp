#include "Archiver/LZ77/LZ77Archiver.h"
#include "Archiver/LZW/LZWArchiver.h"
#include "Archiver/FASTQ/FASTQArchiver.h"
#include "InputOutput/Buffered/BufferedReader.h"
#include "InputOutput/Buffered/BufferedWriter.h"
#include "InputOutput/Bit/BitReader.h"
#include "InputOutput/Bit/BitWriter.h"
#include "InputOutput/StreamReader/StreamReader.h"
#include "Generator/Generator.h"

#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <string>

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_RESET "\x1b[0m"

char* concatenate(const char *s1, const char *s2) {
    char *result = new char[strlen(s1) + strlen(s2) + 1]();
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

int main(int argc, char **argv) {
    if (argc != 4 || (argc > 1 && (strcmp(argv[1], "-c") && strcmp(argv[1], "-d")))) {
        printf(ANSI_COLOR_RED);
        printf("Usage: %s (-c|-d) input_file output_file\n", argv[0]);
        printf(ANSI_COLOR_RESET);
        exit(1);
    }
    FASTQArchiver *archiver = new FASTQArchiver();

    if (!strcmp(argv[1], "-c")) {
        try {
            archiver->Compress(argv[2], argv[3]);
        } catch(const std::string s) {
            printf(ANSI_COLOR_RED);
            printf("An error occured:\n");
            printf(ANSI_COLOR_RESET);

            printf("%s\n", s.c_str());
            return 0;
        }
    } else {
        try {
            archiver->Decompress(argv[2], argv[3]);
        } catch(const std::string s) {
            printf(ANSI_COLOR_RED);
            printf("An error occured:\n");
            printf(ANSI_COLOR_RESET);

            printf("%s\n", s.c_str());
            return 0;
        }
    } 
}
