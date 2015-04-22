#include "LZ78Archiver.h"

#include "../../InputOutput/Interface/Reader.h"
#include "../../InputOutput/Interface/Writer.h"

#include <stdio.h>

LZ78Archiver::LZ78Archiver() {
    m_bor_ = new Bor();
    m_nodes_ptr_ = new BorNode*[m_bor_->get_bor_max_size() + 1];
    m_cur_ = m_bor_->get_cur();

    for (size_t i = 0; i < m_cur_->get_arr_size(); i++)
        m_nodes_ptr_[i + 1] = m_cur_->get_ptr(i);

    m_last_node_from_input_ = NULL;
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

    return s[top - 1];
}

void LZ78Archiver::Compress(Reader *reader, Writer *writer) {
    Bor *bor = new Bor();
    unsigned char ch;
    std::pair<bool, size_t> res;

    while (reader->GetChar(&ch)) {
        res = bor->add_node((char)ch);
        if (res.first) {
            writer->PutShort((short)res.second);
        }
    }

    writer->PutShort((short)bor->get_cur_id());

    writer->Flush();

    delete bor;
}

bool LZ78Archiver::PutNextDecompressedPart(Reader *reader, Writer *writer) {
    bool printed = false;
    unsigned short sh;

    if (!reader->GetShort(&sh))
        return false;

    printed = false;

    if (sh != m_bor_->size() + 1) {
        m_cur_ = m_nodes_ptr_[sh];
        m_last_char_ = PrintSubString(writer, m_bor_, m_s_, m_cur_);
        printed = true;
    }
    
    if (m_last_node_from_input_ != NULL) {
        m_bor_->set_cur(m_last_node_from_input_);
        m_bor_->add_node(m_last_char_);

        BorNode *last_added;
        if ((last_added = m_bor_->get_last_added()) != NULL) {
            m_nodes_ptr_[last_added->get_id()] = last_added;
        }
    }

    if (!printed) {
        m_cur_ = m_nodes_ptr_[sh];
        m_last_char_ = PrintSubString(writer, m_bor_, m_s_, m_cur_);
    }

    m_last_node_from_input_ = m_nodes_ptr_[sh];

    return true;
}

void LZ78Archiver::Decompress(Reader *reader, Writer *writer) {
    while (PutNextDecompressedPart(reader, writer));
    writer->Flush();
}

LZ78Archiver::~LZ78Archiver() {
    delete m_bor_;
    delete [] m_nodes_ptr_;
    delete m_s_;
    delete m_last_node_from_input_;
}
