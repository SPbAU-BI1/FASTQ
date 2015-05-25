#include "Archiver/LZ77/LZ77Archiver.h"
#include "Archiver/Huffman/HuffmanArchiver.h"
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

char* concatenate(const char *s1, const char *s2) {
    char *result = new char[strlen(s1) + strlen(s2) + 1]();
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

int main(int argc, char **argv) {
   	if (argc != 4 || (argc > 1 && (strcmp(argv[1], "-c") && strcmp(argv[1], "-d")))) {
        printf("Usage: %s (-c|-d) input_file output_file\n", argv[0]);
        exit(1);
    }
    FASTQArchiver *archiver = new FASTQArchiver();

    if (!strcmp(argv[1], "-c")) {
        try {
            archiver->Compress(argv[2], argv[3]);
        } catch(const std::string s) {
            printf("An error occured:\n");
            printf("%s\n", s.c_str());
            return 0;
        }
    } else {
        try {
            archiver->Decompress(argv[2], argv[3]);
        } catch(const std::string s) {
            printf("An error occured:\n");
            printf("%s\n", s.c_str());
            return 0;
        }
    }  
	
    /*using std::cerr;
    using std::endl;
    Reader *compress_reader = new BufferedReader(argv[1]);
    Writer *compress_writer = new BitWriter(argv[2]);
 
    HuffmanArchiver *archiver = new HuffmanArchiver();
    std::cerr << "compressing. gonna write to: " << argv[2] << std::endl;
    archiver->Compress(compress_reader, compress_writer);
    delete compress_reader;
    delete compress_writer;
      std::cerr << "done" << argv[2] << std::endl;
    Reader *decompress_reader = new BitReader(argv[2]);
    Writer *decompress_writer = new BufferedWriter(concatenate(argv[1], "_decompressed"));
    std::cerr << "gonna decompress: " << argv[2] << " to " << concatenate(argv[1], "_decompressed") << std::endl;
    archiver->Decompress(decompress_reader, decompress_writer);
 
    delete decompress_reader;
    delete decompress_writer; */
}
