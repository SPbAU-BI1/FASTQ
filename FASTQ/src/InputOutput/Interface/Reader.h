#ifndef _READER_H_
#define _READER_H_

class Reader {
public:
    virtual bool GetChar(unsigned char *val) = 0;
    virtual bool GetShort(unsigned short *val) = 0;
    virtual bool GetInt(unsigned int *val) = 0;
    virtual bool GetLong(unsigned long long *val) = 0;
	virtual Reader* Clone() = 0;

    virtual ~Reader() {}
};

#endif // _READER_H_
