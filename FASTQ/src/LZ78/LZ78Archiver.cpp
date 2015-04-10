#include "LZ78Archiver.h"

#include "../IO/BufferReader.h"
#include "../IO/BufferWriter.h"

LZ78Archiver::LZ78Archiver() {

}

void LZ78Archiver::Compress(const char *input_file_name, const char *output_file_name) {
    BufferReader *br = new BufferReader(input_file_name);
    BufferWriter *bw = new BufferWriter(output_file_name);

    Bor *bor = new Bor();

    unsigned char ch;
    std::pair<bool, size_t> res;

    while (br->get_char(&ch)) {
        res = bor->add_node((char)ch);
        if (res.first) {
            bw->put_short((short)res.second);
        }
    }

    bw->put_short((short)bor->get_cur_id());

    delete bor;
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
