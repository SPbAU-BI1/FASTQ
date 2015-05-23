#ifndef _TRIE_H_
#define _TRIE_H_

#include <utility>
#include <stdlib.h>
#include <limits.h>
#include <list>

#include "TrieNode.h"

class Trie {
public:
    Trie();

    size_t size() const;
    size_t get_cur_id() const;
    size_t get_trie_max_size() const;
    size_t get_next_id() const;
    size_t get_lowest_id() const;

    TrieNode* get_cur();
    TrieNode* get_root();
    TrieNode* get_last_added();

    void set_cur(TrieNode *new_cur);
    
    void add_on_way(TrieNode *cur);
    std::pair<bool, size_t> add_node(char ch);

    ~Trie();
private:
    TrieNode *root_;
    TrieNode *cur_;
    TrieNode *last_added_;

    std::list<TrieNode*> *clear_buckets_;

    size_t size_;
    const size_t kTrieSize;

    void Clear(); // delete kTrieSize / 2 nodes
    void ResetCounts(TrieNode *cur); // reset all counts to zero
    void FillBuckets(TrieNode *cur); // fill clear_buckets_ array
    void DeleteBucket(size_t id); // delete 1 bucket which is passed throw it's index

    bool *is_used_id_;
    size_t lowest_id_free_;
    size_t next_id_free_;

    size_t last_clear_;
    const size_t kToClean;
};

#include "Trie_inline.h"

#endif //_TRIE_H_
