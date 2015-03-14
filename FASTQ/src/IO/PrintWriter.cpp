#include "PrintWriter.h"

PrintWriter::PrintWriter(const char* input_file_name, const char* output_file_name) {
    f_in_ = fopen(input_file_name, "r");
    f_out_ = fopen(output_file_name, "w");

    in_buffer_ = new char[buff_size_];
    out_buffer_ = new char[buff_size_];

    readen_size_ = 0;
    in_buff_l_ = 0;
    out_buff_l_ = 0;
}

char PrintWriter::get_next_char() {
    if (in_buff_l_ == readen_size_) {
        readen_size_ = fread(in_buffer_, sizeof(char), buff_size_, f_in_);
        if (readen_size_ == 0)
            throw "no more chars in input file";

        in_buff_l_ = 0;
    }

    return in_buffer_[in_buff_l_++];
}

void PrintWriter::put_next_char(char ch) {
    if (out_buff_l_ == buff_size_) {
        fwrite(out_buffer_, sizeof(char), buff_size_, f_out_);
        out_buff_l_ = 0;
    }

    out_buffer_[out_buff_l_++] = ch;
}

void PrintWriter::flush() {
    fwrite(out_buffer_, sizeof(char), out_buff_l_, f_out_);
    out_buff_l_ = 0;
}

PrintWriter::~PrintWriter() {
    fclose(f_in_);
    delete in_buffer_;

    if (out_buff_l_ != 0) {
        flush();
    }

    fclose(f_out_);
    delete out_buffer_;
}
