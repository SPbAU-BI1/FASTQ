inline char TrieNode::get_symbol() const {
    return symbol_;
}

inline size_t TrieNode::get_arr_size() const {
    return kArrSize;
}

inline TrieNode* TrieNode::get_father() {
    return father_;
}

inline TrieNode* TrieNode::get_ptr(size_t index) {
    return symbol_ptr_[index];
}

inline void TrieNode::add_ptr(char ch, size_t *size, size_t new_id) {
    size_t index = (size_t)ch;
    symbol_ptr_[index] = new TrieNode(this, ch);
    symbol_ptr_[index]->set_id(new_id);
    (*size)++;
}

//This function is only need for clearing Trie. You shall not use it for any other purposes.
//It may cause memory leaks if you're just using delete_ptr and don't delete element manually.
inline void TrieNode::delete_ptr(char ch, size_t *size) {
    size_t index = (size_t)ch;
    symbol_ptr_[index] = nullptr;
    (*size)--;
}

inline void TrieNode::set_id(size_t new_id) {
    id_ = new_id;
}

inline size_t TrieNode::get_id() const {
    return id_;
}
