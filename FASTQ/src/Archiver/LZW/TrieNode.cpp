#include "TrieNode.h"

TrieNode::TrieNode(TrieNode *father, char symbol): kArrSize(128) {
    symbol_ptr_ = new TrieNode*[kArrSize];
    for (size_t i = 0; i < kArrSize; i++)
        symbol_ptr_[i] = nullptr;

    father_ = father;
    symbol_ = symbol;

    cnt_ = 0;
}

TrieNode::~TrieNode() {
    delete [] symbol_ptr_;
}
