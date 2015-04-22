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
    bool PutNextDecompressedPart(Reader *reader, Writer *writer);
    void Decompress(Reader *reader, Writer *writer);
    ~LZ78Archiver();
private: //some variables which we need during decompress
    Bor *m_bor_;
    BorNode **m_nodes_ptr_;
    BorNode *m_cur_;
    BorNode *m_last_node_from_input_;
    char *m_s_;
    char m_last_char_;
};

#endif // _LZ78ARCHIVER_H_
