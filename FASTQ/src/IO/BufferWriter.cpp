#include "BufferWriter.h"
#include <iostream>

BufferWriter::BufferWriter(const char *output_file_name) {
    f_out_ = fopen(output_file_name, "wb");
    
    out_buffer_ = new char[kBuffSize];
    memset(out_buffer_, 0, kBuffSize);

    out_buff_l_ = 0;
}

BufferWriter::~BufferWriter() {
    flush();
    fclose(f_out_);
    delete out_buffer_;
}
