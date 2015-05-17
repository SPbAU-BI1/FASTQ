#include "LZ78Archiver.h"

#include "../../InputOutput/Interface/Reader.h"
#include "../../InputOutput/Interface/Writer.h"

#include <stdio.h>

LZ78Archiver::LZ78Archiver() {
    m_bor_ = new Bor();
    m_comp_bor_ = new Bor();
    m_nodes_ptr_ = new BorNode*[m_bor_->get_bor_max_size() + 1];
    m_cur_ = m_bor_->get_cur();

    for (size_t i = 0; i < m_cur_->get_arr_size(); i++)
        m_nodes_ptr_[i + 1] = m_cur_->get_ptr(i);
    
    m_last_node_from_input_ = nullptr;
    m_s_ = new char[m_bor_->get_bor_max_size() + 1];
    m_last_char_ = '_';
}

char LZ78Archiver::PrintSubString(Writer *writer, Bor *bor, char *s, BorNode *cur) {
    size_t top = 0;

    while (cur != bor->get_root()) {
        s[top++] = cur->get_symbol();
        cur = cur->get_father();
    }

    for (int i = (int)top - 1; i >= 0; i--) {
        writer->PutChar(s[i]);
    }

    writer->Flush();

    return s[top - 1];
}

void LZ78Archiver::Compress(Reader *reader, Writer *writer) {
    unsigned char ch;
    std::pair<bool, size_t> res;

    while (reader->GetChar(&ch)) {
        res = m_comp_bor_->add_node((char)ch);
        if (res.first) {
            writer->PutShort((unsigned short)res.second); // write next Node code in output, if new vertex were added
        }
    }

    writer->PutShort((unsigned short)m_comp_bor_->get_cur_id());
    writer->Flush();
}

bool LZ78Archiver::PutNextDecompressedPart(Reader *reader, Writer *writer) {
    bool printed = false;
    unsigned short sh;

    if (!reader->GetShort(&sh)) {
        return false;
    }

    if (sh == ((1 << 16) - 1))
        return false;

    printed = false;
// sometimes given node is the one which we were about to add at the previous step
// in this case we handle a normal situations when last added to bot node is not a
// son of last_added
    if (sh != m_bor_->get_lowest_id()) {
        m_cur_ = m_nodes_ptr_[sh];
        m_last_char_ = PrintSubString(writer, m_bor_, m_s_, m_cur_);
        printed = true;
    }
// just checks if this is the first step. If it's not, then we need to add a node to previous cur using last char
    if (m_last_node_from_input_ != nullptr) {
        m_bor_->set_cur(m_last_node_from_input_);
        m_bor_->add_on_way(m_bor_->get_cur()->get_father());
        m_bor_->add_node(m_last_char_); // if sh != m_bor_->... then we are adding new node using previous char;

        BorNode *last_added;
        if ((last_added = m_bor_->get_last_added()) != nullptr) {
            m_nodes_ptr_[last_added->get_id()] = last_added;
        }
    }
// if first condition didn't work, we need to add node and return some string
    if (!printed) {
        m_cur_ = m_nodes_ptr_[sh];
        m_last_char_ = PrintSubString(writer, m_bor_, m_s_, m_cur_);
    }
// current node is the last
    m_last_node_from_input_ = m_nodes_ptr_[sh];

    writer->Flush();
    return true;
}

void LZ78Archiver::Decompress(Reader *reader, Writer *writer) {
    int cnt = 0;
    while (PutNextDecompressedPart(reader, writer)) {
        cnt++;
    }
    writer->Flush();
}

LZ78Archiver::~LZ78Archiver() {
    delete m_bor_;
    delete m_comp_bor_;
    delete [] m_nodes_ptr_;
    delete m_s_;
    delete m_last_node_from_input_;
}
