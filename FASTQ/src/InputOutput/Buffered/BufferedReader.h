#ifndef _BUFFEREDREADER_H_
#define _BUFFEREDREADER_H_

#include "../Interface/Reader.h"

#include <stdio.h>
#include <string.h>
#include <iostream>

class BufferedReader: public Reader {
public:
    BufferedReader(const char *input_file_name);

    bool GetBit(bool *b);
    bool GetChar(unsigned char *ch);
    bool GetShort(unsigned short *sh);

    ~BufferedReader();

private:
    inline void Read();
    FILE *f_in_;
    char *in_buffer_;
    size_t in_buff_l_, readen_size_;
    const size_t kBuffSize = 1000;
};

#endif // BUFFEREDREADER_H_
