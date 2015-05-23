#include "LZWArchiver.h"

#include "../../InputOutput/Interface/Reader.h"
#include "../../InputOutput/Interface/Writer.h"
#include "TrieNode.h"

#include <stdio.h>

LZWArchiver::LZWArchiver() {
    m_comp_trie_ = nullptr;

    m_trie_ = new Trie();
    m_nodes_ptr_ = new TrieNode*[m_trie_->get_trie_max_size() + 1];
    m_cur_ = m_trie_->get_cur();

    for (size_t i = 0; i < m_cur_->get_arr_size(); i++)
        m_nodes_ptr_[i + 1] = m_cur_->get_ptr(i);
    
    m_last_node_from_input_ = nullptr;
    m_s_ = new char[m_trie_->get_trie_max_size() + 1];
    m_last_char_ = '_';
}

bool LZWArchiver::PutNextCompressedPart(Reader *reader, Writer *writer) {
    m_flag_ = false;

    if (reader->GetChar(&m_ch_)) {
        m_res_ = m_comp_trie_->add_node((char)m_ch_);
        if (m_res_.first) {
            writer->PutShort((unsigned short)m_res_.second); // write next Node code in output, if new vertex were added
        }
        m_flag_ = true;
    }

    if (!m_flag_) {
        writer->PutShort((unsigned short)m_comp_trie_->get_cur_id());
    }

    writer->Flush();

    return m_flag_;
}

void LZWArchiver::Compress(Reader *reader, Writer *writer) {
    delete m_comp_trie_;

    m_comp_trie_ = new Trie();
    while (PutNextCompressedPart(reader, writer));
}

char LZWArchiver::PrintSubString(Writer *writer, Trie *trie, char *s, TrieNode *cur) {
    size_t top = 0;

    while (cur != trie->get_root()) {
        s[top++] = cur->get_symbol();
        cur = cur->get_father();
    }

    for (int i = (int)top - 1; i >= 0; i--) {
        writer->PutChar(s[i]);
    }

    writer->Flush();

    return s[top - 1];
}

bool LZWArchiver::PutNextDecompressedPart(Reader *reader, Writer *writer) {
    m_printed_ = false;

    if (!reader->GetShort(&m_sh_)) {
        return false;
    }

    if (m_sh_ == ((1 << 16) - 1))
        return false;

// sometimes given node is the one which we were about to add at the previous step
// in this case we handle a normal situations when last added to bot node is not a
// son of last_added
    if (m_sh_ != m_trie_->get_lowest_id()) {
        m_cur_ = m_nodes_ptr_[m_sh_];
        m_last_char_ = PrintSubString(writer, m_trie_, m_s_, m_cur_);
        m_printed_ = true;
    }
// just checks if this is the first step. If it's not, then we need to add a node to previous cur using last char
    if (m_last_node_from_input_ != nullptr) {
        m_trie_->set_cur(m_last_node_from_input_);
        m_trie_->add_on_way(m_trie_->get_cur()->get_father());
        m_trie_->add_node(m_last_char_); // if sh != m_trie_->... then we are adding new node using previous char;

        TrieNode *last_added;
        if ((last_added = m_trie_->get_last_added()) != nullptr) {
            m_nodes_ptr_[last_added->get_id()] = last_added;
        }
    }
// if first condition didn't work, we need to add node and return some string
    if (!m_printed_) {
        m_cur_ = m_nodes_ptr_[m_sh_];
        m_last_char_ = PrintSubString(writer, m_trie_, m_s_, m_cur_);
    }
// current node is the last
    m_last_node_from_input_ = m_nodes_ptr_[m_sh_];

    writer->Flush();
    return true;
}

void LZWArchiver::Decompress(Reader *reader, Writer *writer) {
    int cnt = 0;
    while (PutNextDecompressedPart(reader, writer)) {
        cnt++;
    }
}

LZWArchiver::~LZWArchiver() {
    delete m_trie_;
    delete m_comp_trie_;
    delete [] m_nodes_ptr_;
    delete m_s_;
    delete m_last_node_from_input_;
}
