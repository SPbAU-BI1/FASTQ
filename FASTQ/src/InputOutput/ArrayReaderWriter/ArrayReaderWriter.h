#ifndef _ARRAYREADERWRITER_H_
#define _ARRAYREADERWRITER_H_

#include "../Interface/Reader.h"
#include "../Interface/Writer.h"

class ArrayReaderWriter: public Reader, public Writer {
public:
    ArrayReaderWriter();
    bool GetChar(unsigned char *ch);
    bool GetShort(unsigned short *sh);
    void PutChar(unsigned char ch);
    void PutShort(unsigned short sh);
    ~ArrayReaderWriter();
private:
    static const int kBufferSize = 1 << 16;
    unsigned char *data_;
    int read_position_;
    int write_position_;
};

#endif //_ARRAYREADERWRITER_H_