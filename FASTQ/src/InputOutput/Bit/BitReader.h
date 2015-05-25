#ifndef _BITREADER_H_
#define _BITREADER_H_

#include "../Interface/Reader.h"

#include <stdio.h>
#include <string.h>
#include <limits>

class BitReader: public Reader {
public:
    BitReader(const char *input_file_name, long long begin_offset = 0, long long end_offset = std::numeric_limits<long long>::max());
    BitReader(const BitReader &reader);
    BitReader* Clone();

    bool GetBit(bool *b);
    bool GetChar(unsigned char *ch);
    bool GetShort(unsigned short *sh);
    bool GetInt(unsigned int *sh);
    bool GetLong(unsigned long long *sh);


    ~BitReader();

private:
    inline void Read();
    FILE *f_in_;
    char *file_name_;
    long long begin_offset_, end_offset_;
    char *in_buffer_;
    size_t in_buff_l_, readen_size_;
    const size_t kBuffSize = 1000;
};

#endif // BITREADER_H_
