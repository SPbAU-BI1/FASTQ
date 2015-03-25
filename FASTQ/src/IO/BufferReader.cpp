#include "BufferReader.h"

BufferReader::BufferReader(const char *input_file_name) {
    f_in_ = fopen(input_file_name, "rb");

    in_buffer_ = new char[kBuffSize];

    readen_size_ = 0;
    in_buff_l_ = 0;
}

void BufferReader::Read() {
    try {
        readen_size_ = fread(in_buffer_, sizeof(char), kBuffSize, f_in_);
        in_buff_l_ = 0;
    } catch(...) {
        throw "Can't read file\n";
    }

    if (readen_size_ == 0) {
        throw "File has been already readen\n";
    }
}

bool BufferReader::get_bit(bool *b) {
    if (in_buff_l_ == readen_size_ * 8) {
        try {
            Read();
        } catch(...) {
            return false;
        }
    }

    size_t index = in_buff_l_ / 8;
    size_t bit_num = in_buff_l_ % 8;
    in_buff_l_++;

    *b = (in_buffer_[index] & (1 << bit_num)) != 0;
    return true;
}

bool BufferReader::get_char(char *ch) {
    *ch = 0;
    bool b;

    for (int i = 0; i < 8; i++) {
        if (!get_bit(&b))
            return false;
        *ch |= b << i;
    }

    return true;
}

bool BufferReader::get_short(short *sh) {
    sh = 0;
    char ch1, ch2;

    if (!(get_char(&ch1) & get_char(&ch2))) {
        return false;
    }

    *sh = (short)ch1 + (short)ch2 * 256;
    return true;
}

BufferReader::~BufferReader() {
    fclose(f_in_);
    delete in_buffer_;
}
