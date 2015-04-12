#ifndef LZ78_BOR_H_
#define LZ78_BOR_H_

#include <utility>
#include <stdlib.h>
#include <climits>

inline size_t symbol_to_number(char ch) {
    switch(ch) {
        case 'A':
            return 0;
        case 'C':
            return 1;
        case 'G':
            return 2;
        case 'T':
            return 3;
        case 'N':
            return 4;
        case 10:
            return 5;
        case 13:
            return 6;
        default:
            throw "Wut?";
    }
}

inline char number_to_symbol(size_t num) {
    switch(num) {
        case 0:
            return 'A';
        case 1:
            return 'C';
        case 2:
            return 'G';
        case 3:
            return 'T';
        case 4:
            return 'N';
        case 5:
            return 10;
        case 6:
            return 13;
        default:
            throw "Wut?";
    }
}

class BorNode {
public:
    BorNode(BorNode *father, char symbol);

    inline BorNode* get_ptr(size_t index);
    inline BorNode* get_father();
    
    inline void add_ptr(size_t ch, size_t *size);
    inline void set_id(size_t new_id);
    
    inline size_t get_id();
    inline size_t get_arr_size();

    inline char get_symbol();

    ~BorNode();
private:
    BorNode **symbol_ptr_;
    size_t id_;
    const size_t kArrSize;
    char symbol_;
    BorNode* father_;
};

inline char BorNode::get_symbol() {
    return symbol_;
}

inline size_t BorNode::get_arr_size() {
    return kArrSize;
}

inline BorNode* BorNode::get_father() {
    return father_;
}

inline BorNode* BorNode::get_ptr(size_t index) {
    return symbol_ptr_[index];
}

inline void BorNode::add_ptr(size_t index, size_t *size) {
    char ch = number_to_symbol(index);
    symbol_ptr_[index] = new BorNode(this, ch);
    (*size)++;
    symbol_ptr_[index]->set_id(*size);
}

inline void BorNode::set_id(size_t new_id) {
    id_ = new_id;
}

inline size_t BorNode::get_id() {
    return id_;
}


class Bor {
public:
    Bor();

    inline size_t size();
    inline size_t get_cur_id();
    inline size_t get_bor_max_size();

    inline BorNode* get_cur();
    inline BorNode* get_root();
    inline BorNode* get_last_added();

    inline void set_cur(BorNode *new_cur);

    std::pair<bool, size_t> add_node(char ch);

    ~Bor();
private:
    BorNode *root_;
    BorNode *cur_;
    BorNode *last_added_;
    size_t size_;
    const size_t kBorSize;
};

inline BorNode* Bor::get_last_added() {
    return last_added_;
}

inline BorNode* Bor::get_cur() {
    return cur_;
}

inline BorNode* Bor::get_root() {
    return root_;
}

inline void Bor::set_cur(BorNode *new_cur) {
    cur_ = new_cur;
}

inline size_t Bor::get_bor_max_size() {
    return kBorSize;
}

inline size_t Bor::get_cur_id() {
    return cur_->get_id();
}

inline size_t Bor::size() {
    return size_;
}

#endif //LZ78_BOR_H_
