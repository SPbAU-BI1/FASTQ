#include "BufferedWriter.h"

BufferedWriter::BufferedWriter(const char *output_file_name) {
    f_out_ = fopen(output_file_name, "wb");
    
    out_buffer_ = new char[kBuffSize];
    memset(out_buffer_, 0, kBuffSize);

    out_buff_l_ = 0;
}

BufferedWriter::~BufferedWriter() {
    Flush();
    fclose(f_out_);
    delete out_buffer_;
}

void BufferedWriter::Flush() {
    fwrite(out_buffer_, sizeof(char), out_buff_l_, f_out_);
    out_buff_l_ = 0;
}

void BufferedWriter::PutChar(unsigned char ch) {
    if (out_buff_l_ == kBuffSize) {
        Flush();
    }

    out_buffer_[out_buff_l_++] = ch;
}

void BufferedWriter::PutShort(unsigned short sh) {
    PutChar(sh & ((1 << 8) - 1));
    PutChar(sh / (1 << 8));
}
