#include "BitReader.h"

BitReader::BitReader(const char *input_file_name) {
    f_in_ = fopen(input_file_name, "rb");

    in_buffer_ = new char[kBuffSize];

    file_name_ = new char[strlen(input_file_name) + 1]();
    strcpy(file_name_, input_file_name);

    readen_size_ = 0;
    in_buff_l_ = 0;
}

BitReader::BitReader(const BitReader &bitReader) {
	BitReader(bitReader.file_name_);
	readen_size_ = bitReader.readen_size_;
	in_buff_l_ = bitReader.in_buff_l_;
	for (int i = 0; i < kBuffSize; i++)
		in_buffer_[i] = bitReader.in_buffer_[i];
}

Reader* BitReader::Clone() {
	return new BitReader(*this);
}

BitReader::~BitReader() {
    fclose(f_in_);
    delete [] in_buffer_;
    delete [] file_name_;
}

bool BitReader::GetBit(bool *b) {
    if (in_buff_l_ == readen_size_ * 8) {
        try {
            Read();
        } catch(...) {
            return false;
        }
    }

    size_t index = in_buff_l_ / 8;
    size_t bit_num = in_buff_l_ % 8;
    in_buff_l_++;

    *b = (in_buffer_[index] & (1 << bit_num)) != 0;
    return true;
}

bool BitReader::GetChar(unsigned char *ch) {
    *ch = 0;
    bool b;

    for (int i = 0; i < 8; i++) {
        if (!GetBit(&b))
            return false;
        *ch |= b << i;
    }
    return true;
}

bool BitReader::GetShort(unsigned short *sh) {
    *sh = 0;
    unsigned char ch1, ch2;

    if (!(GetChar(&ch1) & GetChar(&ch2))) {
        return false;
    }

    *sh = (unsigned short)ch1 + (unsigned short)ch2 * (1 << 8);
    return true;
}

void BitReader::Read() {
    try {
        readen_size_ = fread(in_buffer_, sizeof(char), kBuffSize, f_in_);
        in_buff_l_ = 0;
    } catch(...) {
        throw "Can't read file\n";
    }

    if (readen_size_ == 0) {
        throw "File has been already readen\n";
    }
}
