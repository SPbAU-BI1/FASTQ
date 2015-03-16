#include "BufferReader.h"

BufferReader::BufferReader(const char *input_file_name) {
    f_in_ = fopen(input_file_name, "r");

    in_buffer_ = new char[kBuffSize];

    readen_size_ = 0;
    in_buff_l_ = 0;
}

void BufferReader::Read() {
    try {
        readen_size_ = fread(in_buffer_, sizeof(char), kBuffSize, f_in_);
        in_buff_l_ = 0;
    } catch(...) {
        throw "Cant read file\n";
    }

    if (readen_size_ == 0) {
        throw "File has been already readen\n";
    }
}

bool BufferReader::get_bit() {
    if (in_buff_l_ == readen_size_ * 8) {
        try {
            Read();
        } catch(...) {
            throw;
        }
    }

    size_t index = in_buff_l_ / 8;
    size_t bit_num = in_buff_l_ % 8;
    in_buff_l_++;    

    return (in_buffer_[index] & (1 << bit_num)) != 0;
}

char BufferReader::get_char() {
    char ch = 0;
    for (int i = 0; i < 8; i++) {
        ch |= get_bit() << i;
    }

    return ch;
}

short BufferReader::get_short() {
    short sh = 0;

    try {
        sh |= get_char();
        sh |= (short)(get_char()) * 256;
    } catch(...) {
        throw;
    }

    return sh;
}

BufferReader::~BufferReader() {
    fclose(f_in_);
    delete in_buffer_;
}
