//Cyclic array with opportunity of reading and writing in buffer

#ifndef _ARRAYREADERWRITER_H_
#define _ARRAYREADERWRITER_H_

#include "../Interface/Reader.h"
#include "../Interface/Writer.h"

class ArrayReaderWriter: public Reader, public Writer {
public:
    ArrayReaderWriter();
    ArrayReaderWriter(const ArrayReaderWriter &arrayReaderWriter);
    ArrayReaderWriter* Clone();
    bool GetBit(bool *val) final;
    bool GetChar(unsigned char *val) final;
    bool GetShort(unsigned short *val) final;
    bool GetInt(unsigned int *val) final;
    bool GetLong(unsigned long long *val) final;
    void PutBit(bool val) final;
    void PutChar(unsigned char val) final;
    void PutShort(unsigned short val) final;
    void PutInt(unsigned int val) final;
    void PutLong(unsigned long long val) final;
    void Flush() final;
    
    bool SearchLineFeed(); //Returns true, if there is a symbol '\n' in current buffer
    void PutNextLine(Writer *writer); //Prints symbols till '\n' symbol
    
    ~ArrayReaderWriter();

private:
    void CorrectPosition(int &position); //Corrects position, when it's out of array range 
    static const int kBufferSize = 1 << 16;
    unsigned char *data_;
    int read_position_;
    int write_position_;
};

#include "ArrayReaderWriter_inline.h"

#endif //_ARRAYREADERWRITER_H_