#include "StreamReader.h"

#include <string.h>

StreamReader::StreamReader(const char *input_file_name, int block_size, int row_number): block_size_(block_size), 
                                                                                         row_number_(row_number), 
                                                                                         cur_position_(-1), 
                                                                                         cur_length_(-1) {
    f_in_ = fopen(input_file_name, "r");
    buffer_ = new char[kBufferSize]();
}

StreamReader::~StreamReader() {
    fclose(f_in_);
    delete [] buffer_;
}