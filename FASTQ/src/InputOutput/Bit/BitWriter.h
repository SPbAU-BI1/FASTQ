#ifndef _BITWRITER_H_
#define _BITWRITER_H_

#include "../Interface/Writer.h"

#include <stdio.h>
#include <string.h>

class BitWriter: public Writer {
public:
    BitWriter(const char *output_file_name);

    void PutBit(bool bit);
    void PutChar(unsigned char ch);
    void PutShort(unsigned short sh);
    void Flush();

    ~BitWriter();

private:
    FILE *f_out_;
    char *out_buffer_;
    size_t out_buff_l_;
    const size_t kBuffSize = 1000;
};

#endif // _BITWRITER_H_