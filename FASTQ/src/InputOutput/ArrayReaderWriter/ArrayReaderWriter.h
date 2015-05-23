//Cyclic array with opportunity of reading and writing in buffer

#ifndef _ARRAYREADERWRITER_H_
#define _ARRAYREADERWRITER_H_

#include "../Interface/Reader.h"
#include "../Interface/Writer.h"

class ArrayReaderWriter: public Reader, public Writer {
public:
    ArrayReaderWriter();
    ArrayReaderWriter(const ArrayReaderWriter &arrayReaderWriter);
    Reader* Clone();
    bool GetChar(unsigned char *ch) final;
    bool GetShort(unsigned short *sh) final;
    void PutChar(unsigned char ch) final;
    void PutShort(unsigned short sh) final;
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