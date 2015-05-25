#ifndef _BITWRITER_H_
#define _BITWRITER_H_

#include "../Interface/Writer.h"

#include <stdio.h>
#include <string.h>

class BitWriter: public Writer {
public:
    BitWriter(const char *output_file_name);

    void PutBit(bool val);
    void PutChar(unsigned char val);
    void PutShort(unsigned short val);
    void PutInt(unsigned int val);
    void PutLong(unsigned long long val);
    void Flush();

    void setOffset(long long offset);
    long long getOffset();
    
    ~BitWriter();

private:
    FILE *f_out_;
    char *out_buffer_;
    size_t out_buff_l_;
    const size_t kBuffSize = 1000;
};

#endif // _BITWRITER_H_
