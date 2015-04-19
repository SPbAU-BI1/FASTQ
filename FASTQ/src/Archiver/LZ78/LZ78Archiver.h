#ifndef _LZ78ARCHIVER_H_
#define _LZ78ARCHIVER_H_

#include "../Interface/Archiver.h"

#include <utility>

#include "Bor.h"

class Reader;
class Writer;

class LZ78Archiver : public Archiver {
private:
    char PrintSubString(Writer *writer, Bor *bor, char *s, BorNode *cur);
public:
    LZ78Archiver();
    void Compress(Reader *reader, Writer *writer);
    void Decompress(Reader *reader, Writer *writer);
    ~LZ78Archiver();
};

#endif // _LZ78ARCHIVER_H_
