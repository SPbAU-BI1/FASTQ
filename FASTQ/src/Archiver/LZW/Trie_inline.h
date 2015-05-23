inline TrieNode* Trie::get_last_added() {
    return last_added_;
}

inline TrieNode* Trie::get_cur() {
    return cur_;
}

inline TrieNode* Trie::get_root() {
    return root_;
}

inline void Trie::set_cur(TrieNode *new_cur) {
    cur_ = new_cur;
}

inline size_t Trie::get_trie_max_size() const {
    return kTrieSize;
}

inline size_t Trie::get_cur_id() const {
    return cur_->get_id();
}

inline size_t Trie::size() const {
    return size_;
}

inline size_t Trie::get_next_id() const {
    return next_id_free_;
}

inline size_t Trie::get_lowest_id() const {
    return lowest_id_free_;
}

