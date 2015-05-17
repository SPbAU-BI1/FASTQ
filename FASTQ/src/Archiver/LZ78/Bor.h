#ifndef _BOR_H_
#define _BOR_H_

#include <utility>
#include <stdlib.h>
#include <limits.h>
#include <list>

class BorNode {
public:
    BorNode(BorNode *father, char symbol);

    inline BorNode* get_ptr(size_t index);
    inline BorNode* get_father();

    inline void add_ptr(char ch, size_t *size, size_t new_id);
    inline void delete_ptr(char ch, size_t *size); // see comment below
    inline void set_id(size_t new_id);

    inline size_t get_id() const;
    inline size_t get_arr_size() const;

    inline char get_symbol() const;

    ~BorNode();
public:
    size_t cnt_;
private:
    BorNode **symbol_ptr_;
    BorNode* father_;
    
    const size_t kArrSize;
    size_t id_;

    char symbol_;
};

inline char BorNode::get_symbol() const {
    return symbol_;
}

inline size_t BorNode::get_arr_size() const {
    return kArrSize;
}

inline BorNode* BorNode::get_father() {
    return father_;
}

inline BorNode* BorNode::get_ptr(size_t index) {
    return symbol_ptr_[index];
}

inline void BorNode::add_ptr(char ch, size_t *size, size_t new_id) {
    size_t index = (size_t)ch;
    symbol_ptr_[index] = new BorNode(this, ch);
    symbol_ptr_[index]->set_id(new_id);
    (*size)++;
}
//This function is only need for clearing bor. You shall not use it for any other purposes.
//It may cause memory leaks if you re just using delete_ptr and don't delete element manually.
inline void BorNode::delete_ptr(char ch, size_t *size) {
    size_t index = (size_t)ch;
    symbol_ptr_[index] = nullptr;
    (*size)--;
}

inline void BorNode::set_id(size_t new_id) {
    id_ = new_id;
}

inline size_t BorNode::get_id() const {
    return id_;
}

class Bor {
public:
    Bor();

    inline size_t size() const;
    inline size_t get_cur_id() const;
    inline size_t get_bor_max_size() const;
    inline size_t get_next_id() const;
    inline size_t get_lowest_id() const;

    inline BorNode* get_cur();
    inline BorNode* get_root();
    inline BorNode* get_last_added();

    inline void set_cur(BorNode *new_cur);
    
    void add_on_way(BorNode *cur);
    std::pair<bool, size_t> add_node(char ch);

    ~Bor();
private:
    BorNode *root_;
    BorNode *cur_;
    BorNode *last_added_;

    std::list<BorNode*> *clear_buckets_;

    size_t size_;
    const size_t kBorSize;

    void Clear(); // delete kBorSize / 2 nodes
    void ResetCounts(BorNode *cur); // reset all counts to zero
    void FillBuckets(BorNode *cur); // fill clear_buckets_ array
    void DeleteBucket(size_t id); // delete 1 bucket which is passed throw it's index

    bool *is_used_id_;
    size_t lowest_id_free_;
    size_t next_id_free_;

    size_t last_clear_;
    const size_t kToClean;
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

inline size_t Bor::get_bor_max_size() const {
    return kBorSize;
}

inline size_t Bor::get_cur_id() const {
    return cur_->get_id();
}

inline size_t Bor::size() const {
    return size_;
}

inline size_t Bor::get_next_id() const {
    return next_id_free_;
}

inline size_t Bor::get_lowest_id() const {
    return lowest_id_free_;
}


#endif //_BOR_H_
