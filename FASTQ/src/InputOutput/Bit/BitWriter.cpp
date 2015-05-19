#include "BitWriter.h"

BitWriter::BitWriter(const char *output_file_name) {
    f_out_ = fopen(output_file_name, "wb");
    
    out_buffer_ = new char[kBuffSize];
    memset(out_buffer_, 0, kBuffSize);

    out_buff_l_ = 0;
}

BitWriter::~BitWriter() {
    Flush();
    fclose(f_out_);
    delete out_buffer_;
}

void BitWriter::Flush() {
    fwrite(out_buffer_, sizeof(char), (out_buff_l_ + 7) / 8, f_out_);
    out_buff_l_ = 0;
}

void BitWriter::PutBit(bool bit) {
    if (out_buff_l_ == kBuffSize * 8) {
        Flush();
    }

    size_t index = out_buff_l_ / 8;
    size_t bit_num = out_buff_l_ % 8;

    if (bit_num == 0) {
        out_buffer_[index] = 0;
    }

    out_buffer_[index] |= bit << bit_num;
    out_buff_l_++;
}

void BitWriter::PutChar(unsigned char ch) {
    for (int i = 0; i < 8; i++) {
        PutBit(ch & (1 << i));
    }
}

void BitWriter::PutShort(unsigned short sh) {
    PutChar(sh & ((1 << 8) - 1));
    PutChar(sh / (1 << 8));
}
