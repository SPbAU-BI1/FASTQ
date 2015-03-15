#include "PrintWriter.h"

PrintWriter::PrintWriter(const char* input_file_name, const char* output_file_name) {
    f_in_ = fopen(input_file_name, "r");
    f_out_ = fopen(output_file_name, "w");

    in_buffer_ = new char[kBuffSize];
    out_buffer_ = new char[kBuffSize];
    memset(out_buffer_, 0, sizeof(out_buffer_));

    readen_size_ = 0;
    in_buff_l_ = 0;
    out_buff_l_ = 0;
}

char PrintWriter::get_next_char() {
    if (in_buff_l_ == readen_size_) {
        readen_size_ = fread(in_buffer_, sizeof(char), kBuffSize, f_in_);
        if (readen_size_ == 0)
            throw "no more chars in input file";

        in_buff_l_ = 0;
    }

    return in_buffer_[in_buff_l_++];
}

void PrintWriter::flush() {
    fwrite(out_buffer_, sizeof(char), (out_buff_l_ + 7) / 8, f_out_);
    memset(out_buffer_, 0, sizeof(out_buffer_));
    out_buff_l_ = 0;
}

void PrintWriter::put_next_bit(bool bit) {
    if (out_buff_l_ == kBuffSize * 8) {
        flush();
    }

    size_t index = out_buff_l_ / 8;
    size_t bit_num = out_buff_l_ % 8;
    out_buffer_[index] |= bit << bit_num;
    out_buff_l_++;
}

void PrintWriter::put_next_char(char ch) {
    for (int i = 0; i < 8; i++) {
        put_next_bit(ch & (1 << i));
    }
}

void PrintWriter::put_next_short(short sh) {
    put_next_char((char)(sh & 255));
    put_next_char((char)(sh & (255 << 8)));
}

PrintWriter::~PrintWriter() {
    fclose(f_in_);
    delete in_buffer_;

    flush();

    fclose(f_out_);
    delete out_buffer_;
}
