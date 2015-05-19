#ifndef _BITREADER_H_
#define _BITREADER_H_

#include "../Interface/Reader.h"

#include <stdio.h>
#include <string.h>

class BitReader: public Reader {
public:
    BitReader(const char *input_file_name);

    bool GetBit(bool *b);
    bool GetChar(unsigned char *ch);
    bool GetShort(unsigned short *sh);

    ~BitReader();

private:
    inline void Read();
    FILE *f_in_;
    char *in_buffer_;
    size_t in_buff_l_, readen_size_;
    const size_t kBuffSize = 1000;
};

#endif // BITREADER_H_
