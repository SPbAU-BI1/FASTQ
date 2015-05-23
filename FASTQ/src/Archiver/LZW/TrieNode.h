#ifndef _TRIENODE_H_
#define _TRIENODE_H_

#include <stdlib.h>

class TrieNode {
public:
    TrieNode(TrieNode *father, char symbol);

    TrieNode* get_ptr(size_t index);
    TrieNode* get_father();

    void add_ptr(char ch, size_t *size, size_t new_id);
    void delete_ptr(char ch, size_t *size); // see comment below
    void set_id(size_t new_id);

    size_t get_id() const;
    size_t get_arr_size() const;

    char get_symbol() const;

    ~TrieNode();
public:
    size_t cnt_;
private:
    TrieNode **symbol_ptr_;
    TrieNode* father_;
    
    const size_t kArrSize;
    size_t id_;

    char symbol_;
};

#include "TrieNode_inline.h"

#endif //_TRIENODE_H_