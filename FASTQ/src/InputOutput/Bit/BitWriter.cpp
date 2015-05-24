#include "BitWriter.h"

#include <string>

BitWriter::BitWriter(const char *output_file_name) {
    f_out_ = fopen(output_file_name, "wb");

    if (f_out_ == NULL) {
        std::string name(output_file_name);
        std::string s = "Could not open file named '" + name + "'";
        throw s;
    }

    out_buffer_ = new char[kBuffSize];
    memset(out_buffer_, 0, kBuffSize);

    out_buff_l_ = 0;
}

BitWriter::~BitWriter() {
    Flush();
    fclose(f_out_);
    delete [] out_buffer_;
}

void BitWriter::Flush() {
    fwrite(out_buffer_, sizeof(char), (out_buff_l_ + 7) / 8, f_out_);
    out_buff_l_ = 0;

    if (ferror(f_out_)) {
        throw std::string("Could not writer to output file");
    }
}

void BitWriter::PutBit(bool val) {
    if (out_buff_l_ == kBuffSize * 8) {
        Flush();
    }

    size_t index = out_buff_l_ / 8;
    size_t bit_num = out_buff_l_ % 8;

    if (bit_num == 0) {
        out_buffer_[index] = 0;
    }

    out_buffer_[index] |= val << bit_num;
    out_buff_l_++;
}

void BitWriter::PutChar(unsigned char val) {
    for (int i = 0; i < 8; i++) {
        PutBit(val & (1 << i));
    }
}

void BitWriter::PutShort(unsigned short val) {
    PutChar(val & ((1 << 8) - 1));
    PutChar(val / (1 << 8));
}

void BitWriter::PutInt(unsigned int val) {
    PutShort(val & ((1 << 16) - 1));
    PutShort(val / (1 << 16));
}

void BitWriter::PutLong(unsigned long long val) {
    PutInt(val & ((1ll << 32) - 1));
    PutInt(val / (1ll << 32));
}
