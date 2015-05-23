#ifndef _READER_H_
#define _READER_H_

class Reader {
public:
    virtual bool GetChar(unsigned char *ch) = 0;
    virtual bool GetShort(unsigned short *sh) = 0;
	virtual Reader* Clone() = 0;

    virtual ~Reader() {}
};

#endif // _READER_H_
