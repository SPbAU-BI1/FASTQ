#include "Bor.h"

BorNode::BorNode(BorNode *father, char symbol): kArrSize(7) {
    symbol_ptr_ = new BorNode*[kArrSize];
    for (size_t i = 0; i < kArrSize; i++)
        symbol_ptr_[i] = NULL;
    father_ = father;
    symbol_ = symbol;
}

BorNode::~BorNode() {
    delete [] symbol_ptr_;
}

Bor::Bor(): kBorSize(USHRT_MAX - 5) {
    size_ = 0;
    root_ = new BorNode(NULL, '_');
    cur_ = root_;
    last_added_ = NULL;

    for (size_t i = 0; i < root_->get_arr_size(); i++) {
       root_->add_ptr(i, &size_);
    }
}

std::pair<bool, size_t> Bor::add_node(char ch) {
    BorNode *ptr;
    size_t index = symbol_to_number(ch);
    last_added_ = NULL;

    if ((ptr = cur_->get_ptr(index)) != NULL) {
        cur_ = ptr;
        return std::make_pair(0, cur_->get_id());
    } else {
        size_t ret = cur_->get_id();

        if (size_ <= kBorSize) {
            cur_->add_ptr(index, &size_);
            last_added_ = cur_->get_ptr(index);
            last_added_->set_id(size_); 
        }

        cur_ = root_->get_ptr(index);

        return std::make_pair(1, ret);
    }
}

Bor::~Bor() {
    delete root_;
}
