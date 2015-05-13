#ifndef _WRITER_H_
#define _WRITER_H_

class Writer {
public:
    virtual void PutChar(unsigned char ch) = 0;
    virtual void PutShort(unsigned short sh) = 0;
    virtual void Flush() = 0; //Prints everything that is in buffer now and clar buffer then

    virtual ~Writer() {}
};

#endif // _WRITER_H_
