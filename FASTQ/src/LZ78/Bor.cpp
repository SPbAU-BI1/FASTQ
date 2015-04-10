#include "Bor.h"

BorNode::BorNode(BorNode *father, char symbol): kArrSize(7) {
    symbol_ptr_ = new BorNode*[kArrSize];
    father_ = father;
    symbol_ = symbol;
}

BorNode::~BorNode() {
    delete [] symbol_ptr_;
}

Bor::Bor(): kBorSize(65530) {
    size_ = 0;
    root_ = new BorNode(NULL, '_');
    cur_ = root_;

    for (size_t ch = 0; ch < root_->get_arr_size(); ch++) {
       root_->add_ptr(ch, &size_);
       BorNode *ptr = root_->get_ptr(ch);
       ptr->set_id(size_);
    }
}

std::pair<bool, size_t> Bor::add_node(char ch) {
    BorNode *ptr;
    size_t index = symbol_to_number(ch);

    if ((ptr = cur_->get_ptr(index)) != NULL) {
        cur_ = ptr;
        return std::make_pair(0, cur_->get_id());
    } else {
        size_t ret = cur_->get_id();

        if (size_ <= kBorSize) {
            cur_->add_ptr(index, &size_);
            cur_ = cur_->get_ptr(index);
            cur_->set_id(size_);
        }

        cur_ = root_->get_ptr(index);


        return std::make_pair(1, ret);
    }
}

Bor::~Bor() {
    delete root_;
}
