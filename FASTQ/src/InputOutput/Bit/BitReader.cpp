#include "BitReader.h"

#include <string>

BitReader::BitReader(const char *input_file_name, long long begin_offset, long long end_offset): begin_offset_(begin_offset), 
                                                                                                     end_offset_(end_offset) {
    f_in_ = fopen(input_file_name, "rb");

    if (f_in_ == NULL) {
        std::string name(input_file_name);
        std::string s = "Could not open file named '" + name + "'";
        throw s;
    }

    

    in_buffer_ = new char[kBuffSize];
    file_name_ = new char[strlen(input_file_name) + 1]();
    strcpy(file_name_, input_file_name);

    if (end_offset == std::numeric_limits<long long>::max()) {
        fseek(f_in_, 0, SEEK_END);
        end_offset_ = ftell(f_in_);
    }
    fseek(f_in_, begin_offset_, SEEK_SET);
    readen_size_ = 0;
    in_buff_l_ = 0;
}

BitReader::BitReader(const BitReader &reader): BitReader(reader.file_name_, reader.begin_offset_, reader.end_offset_)  {
    readen_size_ = reader.readen_size_;
    in_buff_l_ = reader.in_buff_l_;
    for (size_t i = 0; i < kBuffSize; i++)
        in_buffer_[i] = reader.in_buffer_[i];
}

BitReader* BitReader::Clone() {
    return new BitReader(*this);
}

BitReader::~BitReader() {
    fclose(f_in_);
    delete [] in_buffer_;
    delete [] file_name_;
}

bool BitReader::GetBit(bool *b) {
    if (in_buff_l_ == readen_size_ * 8) {
        Read();
        if (readen_size_ == 0) {
            return false;
        }
    }

    size_t index = in_buff_l_ / 8;
    size_t bit_num = in_buff_l_ % 8;
    in_buff_l_++;

    *b = (in_buffer_[index] & (1 << bit_num)) != 0;
    return true;
}

bool BitReader::GetChar(unsigned char *val) {
    *val = 0;
    bool b = 0;

    for (int i = 0; i < 8; i++) {
        if (!GetBit(&b))
            return false;
        *val |= b << i;
    }
    return true;
}

bool BitReader::GetShort(unsigned short *val) {
    *val = 0;
    unsigned char val1 = 0, val2 = 0;

    if (!(GetChar(&val1) & GetChar(&val2))) {
        return false;
    }

    *val = (unsigned short)val1 + (unsigned short)val2 * (1 << 8);
    return true;
}

bool BitReader::GetInt(unsigned int *val) {
    *val = 0;
    unsigned short val1 = 0, val2 = 0;

    if (!(GetShort(&val1) & GetShort(&val2))) {
        return false;
    }

    *val = (unsigned int)val1 + (unsigned int)val2 * (1 << 16);
    return true;
}

bool BitReader::GetLong(unsigned long long *val) {
    *val = 0;
    unsigned int val1 = 0, val2 = 0;

    if (!(GetInt(&val1) & GetInt(&val2))) {
        return false;
    }

    *val = (unsigned long long)val1 + (unsigned long long)val2 * (1ll << 32);
    return true;
}


void BitReader::Read() {
    readen_size_ = fread(in_buffer_, sizeof(char), kBuffSize, f_in_);
    in_buff_l_ = 0;

    if (ferror(f_in_)) {
        throw std::string("Could not read input file");
    }
}
