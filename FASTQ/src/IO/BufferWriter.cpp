#include "BufferWriter.h"

BufferWriter::BufferWriter(const char *output_file_name) {
    f_out_ = fopen(output_file_name, "w");

    out_buffer_ = new char[kBuffSize];
    memset(out_buffer_, 0, sizeof(out_buffer_));

    out_buff_l_ = 0;
}

void BufferWriter::flush() {
    fwrite(out_buffer_, sizeof(char), (out_buff_l_ + 7) / 8, f_out_);
    memset(out_buffer_, 0, sizeof(out_buffer_));
    out_buff_l_ = 0;
}

void BufferWriter::put_bit(bool bit) {
    if (out_buff_l_ == kBuffSize * 8) {
        flush();
    }

    size_t index = out_buff_l_ / 8;
    size_t bit_num = out_buff_l_ % 8;
    out_buffer_[index] |= bit << bit_num;
    out_buff_l_++;
}

void BufferWriter::put_char(char ch) {
    for (int i = 0; i < 8; i++) {
        put_bit(ch & (1 << i));
    }
}

void BufferWriter::put_short(short sh) {
    put_char(sh & ((1 << 8) - 1));
    put_char(sh / (1 << 8));
}

BufferWriter::~BufferWriter() {
    flush();
    fclose(f_out_);
    delete out_buffer_;
}
