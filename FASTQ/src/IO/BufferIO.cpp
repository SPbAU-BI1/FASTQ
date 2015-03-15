#include "BufferIO.h"

BufferReader::BufferReader(const char *input_file_name) {
    f_in_ = fopen(input_file_name, "r");

    in_buffer_ = new char[kBuffSize];

    readen_size_ = 0;
    in_buff_l_ = 0;
}

void BufferReader::Read() {
    try {
        readen_size_ = fread(in_buffer_, sizeof(char), kBuffSize, f_in_);
        in_buff_l_ = 0;
    } catch(...) {
        throw "Cant read file\n";
    }

    if (readen_size_ == 0) {
        throw "File has been already readen\n";
    }
}

bool BufferReader::get_next_bit() {
    if (in_buff_l_ == readen_size_ * 8) {
        try {
            Read();
        } catch(...) {
            throw;
        }
    }

    size_t index = in_buff_l_ / 8;
    size_t bit_num = in_buff_l_ % 8;
    in_buff_l_++;    

    return (in_buffer_[index] & (1 << bit_num)) != 0;
}

char BufferReader::get_next_char() {
    char ch = 0;
    for (int i = 0; i < 8; i++) {
        ch |= get_next_bit() << i;
    }

    return ch;
}

short BufferReader::get_next_short() {
    short sh = 0;

    try {
        sh |= get_next_char();
        sh |= (short)(get_next_char()) * 256;
    } catch(...) {
        throw;
    }

    return sh;
}

BufferReader::~BufferReader() {
    fclose(f_in_);
    delete in_buffer_;
}

/* BufferWriter part */

BufferWriter::BufferWriter(const char *output_file_name) {
    f_out_ = fopen(output_file_name, "w");

    out_buffer_ = new char[kBuffSize];
    memset(out_buffer_, 0, sizeof(out_buffer_));

    out_buff_l_ = 0;
}

void BufferWriter::flush() {
    fwrite(out_buffer_, sizeof(char), (out_buff_l_ + 7) / 8, f_out_);
    memset(out_buffer_, 0, sizeof(out_buffer_));
    out_buff_l_ = 0;
}

void BufferWriter::put_next_bit(bool bit) {
    if (out_buff_l_ == kBuffSize * 8) {
        flush();
    }

    size_t index = out_buff_l_ / 8;
    size_t bit_num = out_buff_l_ % 8;
    out_buffer_[index] |= bit << bit_num;
    out_buff_l_++;
}

void BufferWriter::put_next_char(char ch) {
    for (int i = 0; i < 8; i++) {
        put_next_bit(ch & (1 << i));
    }
}

void BufferWriter::put_next_short(short sh) {
    put_next_char(sh & 255);
    put_next_char(sh / 256);
}

BufferWriter::~BufferWriter() {
    flush();
    fclose(f_out_);
    delete out_buffer_;
}
