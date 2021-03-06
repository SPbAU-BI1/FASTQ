#include "BufferedWriter.h"

#include <string>

BufferedWriter::BufferedWriter(const char *output_file_name) {
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

BufferedWriter::~BufferedWriter() {
    Flush();
    fclose(f_out_);
    delete [] out_buffer_;
}

