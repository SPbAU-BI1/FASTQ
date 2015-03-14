#include "LZ78Archiver.h"
#include "../IO/PrintWriter.h"

LZ78Archiver::LZ78Archiver() {

}

void LZ78Archiver::Compress(const char *input_file_name, const char *output_file_name) {
    PrintWriter *pw = new PrintWriter(input_file_name, output_file_name);

    delete pw;
}

void LZ78Archiver::Decompress(const char *input_file_name, const char *output_file_name) {
    PrintWriter *pw = new PrintWriter(input_file_name, output_file_name);

    delete pw;
}

LZ78Archiver::~LZ78Archiver() {

}
