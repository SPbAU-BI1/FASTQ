#ifndef _WRITER_H_
#define _WRITER_H_

class Writer {
public:
    virtual void PutBit(bool val) = 0;
    virtual void PutChar(unsigned char val) = 0;
    virtual void PutShort(unsigned short val) = 0;
    virtual void PutInt(unsigned int val) = 0;
    virtual void PutLong(unsigned long long val) = 0;
    virtual void Flush() = 0; //Prints everything that is in buffer now and clar buffer then

    virtual ~Writer() {}
};

#endif // _WRITER_H_
