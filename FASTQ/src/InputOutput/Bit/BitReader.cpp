#include "BitReader.h"

BitReader::BitReader(const char *input_file_name) {
    f_in_ = fopen(input_file_name, "rb");

    in_buffer_ = new char[kBuffSize];

    readen_size_ = 0;
    in_buff_l_ = 0;
}

BitReader::~BitReader() {
    fclose(f_in_);
    delete in_buffer_;
}

bool BitReader::GetBit(bool *b) {
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

bool BitReader::GetChar(unsigned char *ch) {
    *ch = 0;
    bool b;

    for (int i = 0; i < 8; i++) {
        if (!GetBit(&b))
            return false;
        *ch |= b << i;
    }
    return true;
}

bool BitReader::GetShort(unsigned short *sh) {
    *sh = 0;
    unsigned char ch1, ch2;

    if (!(GetChar(&ch1) & GetChar(&ch2))) {
        return false;
    }

    *sh = (unsigned short)ch1 + (unsigned short)ch2 * (1 << 8);
    return true;
}

void BitReader::Read() {
    try {
        memset(in_buffer_, 0, kBuffSize);
        readen_size_ = fread(in_buffer_, sizeof(char), kBuffSize, f_in_);
        in_buff_l_ = 0;
    } catch(...) {
        throw "Can't read file\n";
    }

    if (readen_size_ == 0) {
        throw "File has been already readen\n";
    }
}
