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

void BufferedWriter::PutChar(unsigned char val) {
    if (out_buff_l_ == kBuffSize) {
        Flush();
    }

    out_buffer_[out_buff_l_++] = val;
}

void BufferedWriter::PutShort(unsigned short val) {
    PutChar(val & ((1 << 8) - 1));
    PutChar(val >> 8);
}

void BufferedWriter::PutInt(unsigned int val) {
    PutShort(val & ((1 << 16) - 1));
    PutShort(val >> 16);
}

void BufferedWriter::PutLong(unsigned long long val) {
    PutInt(val & ((1ll << 32) - 1));
    PutInt(val >> 32);
}

void BufferedWriter::setOffset(long long offset)
{
    Flush();
    fseek(f_out_, offset, SEEK_SET);
}

long long BufferedWriter::getOffset()
{
    Flush();
    return ftell(f_out_);
}
