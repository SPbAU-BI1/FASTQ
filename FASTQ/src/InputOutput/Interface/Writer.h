#ifndef _WRITER_H_
#define _WRITER_H_

#include <stdio.h>
#include <string.h>

class Writer {
public:
    virtual void put_char(unsigned char ch) = 0;
    virtual void put_short(unsigned short sh) = 0;

    virtual ~Writer() {}
};

#endif // _WRITER_H_
