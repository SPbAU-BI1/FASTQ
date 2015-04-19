#ifndef _BUFFEREDWRITER_H_
#define _BUFFEREDWRITER_H_

#include "../Interface/Writer.h"

#include <stdio.h>
#include <string.h>

class BufferedWriter: public Writer {
public:
    BufferedWriter(const char *output_file_name);

    void flush();

    void put_bit(bool bit);
    void put_char(unsigned char ch);
    void put_short(unsigned short sh);

    ~BufferedWriter();

private:
    FILE *f_out_;
    char *out_buffer_;
    size_t out_buff_l_;
    const size_t kBuffSize = 1000;
};

#endif // _BUFFEREDWRITER_H_
