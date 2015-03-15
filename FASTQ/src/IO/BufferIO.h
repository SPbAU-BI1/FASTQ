#ifndef LZ78_PRINTWRITER_H_
#define LZ78_PRINTWRITER_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

class BufferReader {
private:
    FILE *f_in_;
    char *in_buffer_;
    size_t in_buff_l_, readen_size_;
    const size_t kBuffSize = 1000;

    void Read();
public:
    BufferReader(const char *input_file_name);

    bool get_next_bit();
    char get_next_char();
    short get_next_short();

    ~BufferReader();
};


class BufferWriter {
private:
    FILE *f_out_;
    char *out_buffer_;
    size_t out_buff_l_;
    const size_t kBuffSize = 1000;
public:
    BufferWriter(const char *output_file_name);

    void flush();
    void put_next_bit(bool bit);
    void put_next_char(char ch);
    void put_next_short(short sh);

    ~BufferWriter();
};

#endif // LZ78_PRINTWRITER_H_
