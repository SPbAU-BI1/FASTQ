#include "BufferReader.h"

BufferReader::BufferReader(const char *input_file_name) {
    f_in_ = fopen(input_file_name, "rb");

    in_buffer_ = new char[kBuffSize];

    readen_size_ = 0;
    in_buff_l_ = 0;
}

BufferReader::~BufferReader() {
    fclose(f_in_);
    delete in_buffer_;
}
