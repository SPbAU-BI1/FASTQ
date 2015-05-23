#ifndef _BUFFEREDWRITER_H_
#define _BUFFEREDWRITER_H_

#include "../Interface/Writer.h"

#include <stdio.h>
#include <string.h>

class BufferedWriter: public Writer {
public:
    BufferedWriter(const char *output_file_name);

    void PutChar(unsigned char val);
    void PutShort(unsigned short val);
    void PutInt(unsigned int val);
    void PutLong(unsigned long long val);
    void Flush();
    
    void setOffset(long long offset);
    long long getOffset();

    ~BufferedWriter();

private:
    FILE *f_out_;
    char *out_buffer_;
    size_t out_buff_l_;
    const size_t kBuffSize = (1 << 16);
};

#endif // _BUFFEREDWRITER_H_
