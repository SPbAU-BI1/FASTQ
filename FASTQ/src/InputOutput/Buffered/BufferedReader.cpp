#include "BufferedReader.h"

#include <algorithm>

BufferedReader::BufferedReader(const char *input_file_name, long long begin_offset, long long end_offset): begin_offset_(begin_offset), 
                                                                                                     end_offset_(end_offset) {
    f_in_ = fopen(input_file_name, "rb");
    
    in_buffer_ = new char[kBuffSize];
    file_name_ = new char[strlen(input_file_name) + 1]();
    strcpy(file_name_, input_file_name);

    if (end_offset == std::numeric_limits<long long>::max())
    {
        fseek(f_in_, 0, SEEK_END);
        end_offset_ = ftell(f_in_);
    }
    
    fseek(f_in_, begin_offset_, SEEK_SET);
    readen_size_ = 0;
    in_buff_l_ = 0;
}

BufferedReader::BufferedReader(const BufferedReader &reader)
{
    BufferedReader(reader.file_name_, reader.begin_offset_, reader.end_offset_);
    fseek(f_in_, ftell(reader.f_in_), SEEK_SET); 
}

BufferedReader::~BufferedReader() {
    fclose(f_in_);
    delete in_buffer_;
    delete file_name_;
}

bool BufferedReader::GetChar(unsigned char *val) {
    if (in_buff_l_ == readen_size_) {
        try {
            Read();
        } catch(...) {
            return false;
        }
    }

    *val = in_buffer_[in_buff_l_++];
    
    return true;
}

bool BufferedReader::GetShort(unsigned short *val) {
    *val = 0;
    unsigned char val1, val2;

    if (!(GetChar(&val1) & GetChar(&val2))) {
        return false;
    }

    *val = (unsigned short) val1 + (unsigned short) val2 * (1 << 8);
    return true;
}

bool BufferedReader::GetInt(unsigned int *val) {
    *val = 0;
    unsigned short val1, val2;

    if (!(GetShort(&val1) & GetShort(&val2))) {
        return false;
    }

    *val = (unsigned int) val1 + (unsigned int) val2 * (1 << 16);
    return true;
}

bool BufferedReader::GetLong(unsigned long long *val) {
    *val = 0;
    unsigned int val1, val2;

    if (!(GetInt(&val1) & GetInt(&val2))) {
        return false;
    }

    *val = (unsigned long long) val1 + (unsigned long long) val2 * (1ll << 32);
    return true;
}

void BufferedReader::Read() {
    try {
        long long remaining_offset = end_offset_ - ftell(f_in_);
        readen_size_ = fread(in_buffer_, sizeof(char), std::min((long long) kBuffSize, remaining_offset), f_in_);
        in_buff_l_ = 0;
    } catch(...) {
        throw "Can't read file\n";
    }

    if (readen_size_ == 0) {
        throw "File has been already readen\n";
    }
}

