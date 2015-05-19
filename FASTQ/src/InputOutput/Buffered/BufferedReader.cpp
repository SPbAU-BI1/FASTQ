#include "BufferedReader.h"

BufferedReader::BufferedReader(const char *input_file_name) {
    f_in_ = fopen(input_file_name, "rb");

    in_buffer_ = new char[kBuffSize];

    readen_size_ = 0;
    in_buff_l_ = 0;
}

BufferedReader::~BufferedReader() {
    fclose(f_in_);
    delete in_buffer_;
}

bool BufferedReader::GetChar(unsigned char *ch) {
    if (in_buff_l_ == readen_size_) {
        try {
            Read();
        } catch(...) {
            return false;
        }
    }

    *ch = in_buffer_[in_buff_l_++];
    
    return true;
}

bool BufferedReader::GetShort(unsigned short *sh) {
    *sh = 0;
    unsigned char ch1, ch2;

    if (!(GetChar(&ch1) & GetChar(&ch2))) {
        return false;
    }

    *sh = (unsigned short)ch1 + (unsigned short)ch2 * (1 << 8);
    return true;
}

void BufferedReader::Read() {
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

