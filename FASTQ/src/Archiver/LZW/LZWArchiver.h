#ifndef _LZWARCHIVER_H_
#define _LZWARCHIVER_H_

#include "../Interface/Archiver.h"

#include <utility>

#include "Trie.h"

class Reader;
class Writer;

class LZWArchiver : public Archiver {
private:
    char PrintSubString(Writer *writer, Trie *trie, char *s, TrieNode *cur);
public:
    LZWArchiver();
    bool PutNextCompressedPart(Reader *reader, Writer *writer);
    void Compress(Reader *reader, Writer *writer);
    bool PutNextDecompressedPart(Reader *reader, Writer *writer);
    void Decompress(Reader *reader, Writer *writer);
    ~LZWArchiver();
private: //some variables which we need during decompress
    Trie *m_comp_trie_;
    Trie *m_trie_;
    TrieNode **m_nodes_ptr_;
    TrieNode *m_cur_;
    TrieNode *m_last_node_from_input_;
    char *m_s_;
    char m_last_char_;
    unsigned char m_ch_;
    std::pair<bool, size_t> m_res_;
    bool m_flag_;
    unsigned short m_sh_;
    bool m_printed_;
};

#endif // _LZWARCHIVER_H_
