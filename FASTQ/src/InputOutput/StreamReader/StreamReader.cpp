#include "StreamReader.h"

#include <string.h>

StreamReader::StreamReader(const char *input_file_name, int block_size, int row_number): block_size_(block_size), 
                                                                                         row_number_(row_number), 
                                                                                         cur_position_(-1), 
                                                                                         cur_length_(-1) {
    f_in_ = fopen(input_file_name, "r");
    buffer_ = new char[kBufferSize]();
}

bool StreamReader::GetChar(unsigned char *ch) {
    if (cur_position_ == cur_length_) {
        int read_row_count = block_size_;
        if (cur_length_ == -1)                      
            read_row_count = row_number_ + 1;
        //Reads block of unnecessary lines
        for (int i = 0; i < read_row_count; i++)
            if (fgets(buffer_, kBufferSize - 1, f_in_) == NULL)
                return 0;
        cur_position_ = 0;
        cur_length_ = strlen(buffer_);
    }
    *ch = buffer_[cur_position_++];
    return 1;   
}

bool StreamReader::GetShort(unsigned short *sh) {
    unsigned char ch1, ch2;
    if (!GetChar(&ch1))
        return 0;
    if (!GetChar(&ch2))
        return 0;
    *sh = ch1 * (1 << 8) + ch2;
    return 1;
}

StreamReader::~StreamReader() {
    fclose(f_in_);
    delete [] buffer_;
}