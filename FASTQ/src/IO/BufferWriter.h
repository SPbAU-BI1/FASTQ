#ifndef IO_BUFFERWRITER_H_
#define IO_BUFFERWRITER_H_

#include <stdio.h>
#include <string.h>

class BufferWriter {
public:
    BufferWriter(const char *output_file_name);

    void flush();
    void put_next_bit(bool bit);
    void put_next_char(char ch);
    void put_next_short(short sh);

    ~BufferWriter();
private:
    FILE *f_out_;
    char *out_buffer_;
    size_t out_buff_l_;
    const size_t kBuffSize = 1000;
};

#endif // IO_BUFFERWRITER_H_
