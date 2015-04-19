//Interface for archivers

#ifndef _ARCHIVER_H_
#define _ARCHIVER_H_

#include <cstdio>

class Reader;
class Writer;

class Archiver {
public:
    //Compresses data read from reader and saves it to writer
    virtual void Compress(Reader *reader, Writer *writer) = 0;
    //Decompresses data read from reader and saves it to writer
    virtual void Decompress(Reader *reader, Writer *writer) = 0;
    virtual ~Archiver() {}
};

#endif // _INTERFACE_ARCHIVER_H_
