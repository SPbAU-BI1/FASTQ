#include "LZ77/LZ77Archiver.h"
#include "IO/BufferIO.h"

#include <stdlib.h>

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_RESET "\x1b[0m"

int main(int argc, char **argv) {
    if (argc != 3) {
        printf(ANSI_COLOR_RED);
        printf("Error! You need to pass exactly 2 arguments: input and output files.\n");
        printf(ANSI_COLOR_RESET);
        exit(1);
    }

    Archiver *archiver = new LZ77Archiver();
    archiver->Compress(argv[1], argv[2]);

    delete archiver;
// IO test

    char ch;
    BufferReader *br = new BufferReader(argv[1]);
    BufferWriter *bw = new BufferWriter(argv[2]);

    while (true) {
        try {
            ch = br->get_next_char();
        } catch(...) {
            break;
        }

        bw->put_next_char(ch);
    }

    delete bw;
    delete br;
}
