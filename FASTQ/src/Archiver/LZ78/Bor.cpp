#include "Bor.h"
    
BorNode::BorNode(BorNode *father, char symbol): kArrSize(128) {
    symbol_ptr_ = new BorNode*[kArrSize];
    for (size_t i = 0; i < kArrSize; i++)
        symbol_ptr_[i] = nullptr;

    father_ = father;
    symbol_ = symbol;

    cnt_ = 0;
}

BorNode::~BorNode() {
    delete [] symbol_ptr_;
}

Bor::Bor(): kBorSize(USHRT_MAX - 1), kToClean(5000) {
    size_ = 0;
    last_clear_ = 0;
    root_ = new BorNode(nullptr, 0);
    cur_ = root_;
    last_added_ = nullptr;
    clear_buckets_ = new std::list<BorNode*>[kBorSize + 2];

    is_used_id_ = new bool[kBorSize + 2];
    for (size_t i = 0; i < kBorSize + 2; i++)
        is_used_id_[i] = false;
    is_used_id_[0] = true;
    lowest_id_free_ = 1;

    for (size_t i = 0; i < root_->get_arr_size(); i++) {
        root_->add_ptr(i, &size_, lowest_id_free_);
        is_used_id_[lowest_id_free_] = true;
        lowest_id_free_++;
    }
    next_id_free_ = lowest_id_free_ + 1;
}

std::pair<bool, size_t> Bor::add_node(char ch) {
    BorNode *ptr;
    size_t index = (size_t)ch;
    last_added_ = nullptr;

    if (cur_->cnt_ <= kBorSize)
        cur_->cnt_++;

    if ((ptr = cur_->get_ptr(index)) != nullptr) {
        cur_ = ptr;
        return std::make_pair(0, cur_->get_id());
    } else {
        size_t ret = cur_->get_id();
        last_clear_++;

        if (size_ < kBorSize) {
            cur_->add_ptr(ch, &size_, lowest_id_free_);

            last_added_ = cur_->get_ptr(index);

            is_used_id_[lowest_id_free_] = true;
            lowest_id_free_ = next_id_free_;
            next_id_free_++;
            while (next_id_free_ <= kBorSize && is_used_id_[next_id_free_])
                next_id_free_++;
        } else {
            if (last_clear_ >= size_)
                Clear();
        }

        cur_ = root_->get_ptr(index);

        return std::make_pair(1, ret);
    }
}

void Bor::add_on_way(BorNode *cur) {
    while (cur != root_) {
        if (cur->cnt_ <= kBorSize)
            cur->cnt_++;
        else
            break;
        cur = cur->get_father();
    }
}

void Bor::ResetCounts(BorNode *cur) {
    cur->cnt_ = 0;

    for (size_t i = 0; i < cur->get_arr_size(); i++) {
        if (cur->get_ptr(i) != nullptr)
            ResetCounts(cur->get_ptr(i));
    }
}

void Bor::FillBuckets(BorNode *cur) {
    if (cur != root_ && cur->get_father() != root_ && cur->cnt_ <= kBorSize) {
        clear_buckets_[cur->cnt_].push_front(cur);
    }

    for (size_t i = 0; i < cur->get_arr_size(); i++) {
        if (cur->get_ptr(i) != nullptr) {
            FillBuckets(cur->get_ptr(i));
        }
    }
}

void Bor::DeleteBucket(size_t id) {
    std::list<BorNode*> to_delete;

    while(clear_buckets_[id].size()) {
        BorNode *cur = clear_buckets_[id].front();
        clear_buckets_[id].pop_front();

        cur->get_father()->delete_ptr(cur->get_symbol(), &size_);
        is_used_id_[cur->get_id()] = false;

        if (lowest_id_free_ < cur->get_id())
            next_id_free_ = std::min(cur->get_id(), next_id_free_);
        else {
            next_id_free_ = lowest_id_free_;
            lowest_id_free_ = cur->get_id();
        }

        to_delete.push_front(cur);
    }

    while (to_delete.size()) {
        delete to_delete.front();
        to_delete.pop_front();
    }
}

void Bor::Clear() {
    for (size_t i = 0; i < kBorSize + 2; i++) {
        if (!clear_buckets_[i].empty())
            clear_buckets_[i].clear();
    }

    FillBuckets(root_);

    double ratio = std::max(0.0, (double)(size_ - kToClean) / size_);
    int new_size = (int)(size_ * ratio);
    for (size_t i = 0; i < kBorSize; i++) {
        if ((int) size_ > new_size && !clear_buckets_[i].empty()) {
            DeleteBucket(i);
        }
    }

    last_clear_ = 0;
//    ResetCounts(root_); //without it algorithm works better.
}

Bor::~Bor() {
    delete root_;
}
