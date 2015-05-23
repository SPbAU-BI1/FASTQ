#ifndef _BUFFEREDREADER_H_
#define _BUFFEREDREADER_H_

#include "../Interface/Reader.h"

#include <stdio.h>
#include <string.h>
#include <limits>

class BufferedReader: public Reader {
public:
    BufferedReader(const char *input_file_name, fpos_t begin_offset = std::numeric_limits<fpos_t>::min(), fpos_t end_offset = std::numeric_limits<fpos_t>::max());
    BufferedReader(const BufferedReader &reader);
    bool GetChar(unsigned char *val);
    bool GetShort(unsigned short *val);
    bool GetInt(unsigned int *val);
    bool GetLong(unsigned long long *val);

    ~BufferedReader();

private:
    inline void Read();
    char *file_name_;
    fpos_t begin_offset_, end_offset_;
    FILE *f_in_;
    char *in_buffer_;
    size_t in_buff_l_, readen_size_;
    const size_t kBuffSize = (1 << 16);
};

#endif // BUFFEREDREADER_H_
