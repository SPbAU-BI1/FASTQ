#ifndef IO_BUFFERREADER_H_
#define IO_BUFFERREADER_H_

#include <stdio.h>
#include <string.h>

class BufferReader {
public:
    BufferReader(const char *input_file_name);

    bool get_bit(bool *b);
    bool get_char(char * ch);
    bool get_short(short *sh);

    ~BufferReader();
private:
    void Read();

    FILE *f_in_;
    char *in_buffer_;
    size_t in_buff_l_, readen_size_;
    const size_t kBuffSize = 1000;
};

#endif // IO_BUFFERREADER_H_
