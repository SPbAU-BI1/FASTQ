#ifndef _BUFFEREDREADER_H_
#define _BUFFEREDREADER_H_

#include "../Interface/Reader.h"

#include <stdio.h>
#include <string.h>
#include <limits>
#include <algorithm>

class BufferedReader: public Reader {
public:
    BufferedReader(const char *input_file_name, long long begin_offset = 0, long long end_offset = std::numeric_limits<long long>::max());
    BufferedReader(const BufferedReader &reader);
    Reader* Clone();
    bool GetChar(unsigned char *val) final;
    bool GetShort(unsigned short *val) final;
    bool GetInt(unsigned int *val);
    bool GetLong(unsigned long long *val);

    ~BufferedReader();

private:
    inline void Read();
    char *file_name_;
    long long begin_offset_, end_offset_;
    FILE *f_in_;
    char *in_buffer_;
    size_t in_buff_l_, readen_size_;
    const size_t kBuffSize = (1 << 16);
};

#include "BufferedReader_inline.h"

#endif // BUFFEREDREADER_H_
