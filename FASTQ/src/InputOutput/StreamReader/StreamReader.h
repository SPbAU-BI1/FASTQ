#ifndef _STREAMREADER_H_
#define _STREAMREADER_H_

#include "../Interface/Reader.h"

#include <stdio.h>

class StreamReader: public Reader {
public:
    StreamReader(const char *input_file_name, int block_size, int row_number);
    
    bool GetChar(unsigned char *ch);
    bool GetShort(unsigned short *sh);

    ~StreamReader();
private:
    static const int kBufferSize = 1 << 16;
    FILE *f_in_;
    int block_size_;
    int row_number_;
    int cur_position_;
    int cur_length_;
    char *buffer_;
};

#endif //_STREAMREADER_H_