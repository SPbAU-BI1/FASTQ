#include "LZ78Archiver.h"

#include "../IO/BufferReader.h"
#include "../IO/BufferWriter.h"

LZ78Archiver::LZ78Archiver() {

}

void LZ78Archiver::Compress(const char *input_file_name, const char *output_file_name) {
    BufferReader *br = new BufferReader(input_file_name);
    BufferWriter *bw = new BufferWriter(output_file_name);

    delete br;
    delete bw;
}

void LZ78Archiver::Decompress(const char *input_file_name, const char *output_file_name) {
    BufferReader *br = new BufferReader(input_file_name);
    BufferWriter *bw = new BufferWriter(output_file_name);

    delete bw;
    delete br;
}

LZ78Archiver::~LZ78Archiver() {

}
