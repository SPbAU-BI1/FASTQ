#ifndef _READER_H_
#define _READER_H_

#include <stdio.h>
#include <string.h>
#include <iostream>

class Reader {
public:
    virtual bool get_char(unsigned char *ch) = 0;
    virtual bool get_short(unsigned short *sh) = 0;

    virtual ~Reader() {}
};

#endif // _READER_H_
