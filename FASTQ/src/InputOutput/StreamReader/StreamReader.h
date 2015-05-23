//Reads only lines such it's number is row_number mod block_size

#ifndef _STREAMREADER_H_
#define _STREAMREADER_H_

#include "../Interface/Reader.h"

#include <stdio.h>

class StreamReader: public Reader {
public:
    StreamReader(const char *input_file_name, int block_size, int row_number);
    StreamReader(const StreamReader &reader);
    Reader* Clone();

    bool GetChar(unsigned char *ch) final;
    bool GetShort(unsigned short *sh) final;

    ~StreamReader();
private:
    static const int kBufferSize = 1 << 16;
    FILE *f_in_;
    char *file_name_;
    int block_size_;
    int row_number_;
    int cur_position_;
    int cur_length_;
    char *buffer_;
};

#include "StreamReader_inline.h"

#endif //_STREAMREADER_H_