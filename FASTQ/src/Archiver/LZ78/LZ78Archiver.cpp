#include "LZ78Archiver.h"

#include "../../InputOutput/Interface/Reader.h"
#include "../../InputOutput/Interface/Writer.h"

#include <stdio.h>

LZ78Archiver::LZ78Archiver() {

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

    delete bor;
}

void LZ78Archiver::Decompress(Reader *reader, Writer *writer) {
    Bor *bor = new Bor();
    BorNode **nodes_ptr = new BorNode*[bor->get_bor_max_size() + 1];
    BorNode *cur = bor->get_cur();

    for (size_t i = 0; i < cur->get_arr_size(); i++)
        nodes_ptr[i + 1] = cur->get_ptr(i);

    BorNode *last_node_from_input = NULL;
    unsigned short sh;
    char *s = new char[bor->get_bor_max_size() + 1];
    char last_char = '_';
    bool printed = false;

    while (reader->GetShort(&sh)) {
        printed = false;

        if (sh != bor->size() + 1) {
            cur = nodes_ptr[sh];
            last_char = PrintSubString(writer, bor, s, cur);
            printed = true;
        }
        
        if (last_node_from_input != NULL) {
            bor->set_cur(last_node_from_input);
            bor->add_node(last_char);

            BorNode *last_added;
            if ((last_added = bor->get_last_added()) != NULL) {
                nodes_ptr[last_added->get_id()] = last_added;
            }
        }

        if (!printed) {
            cur = nodes_ptr[sh];
            last_char = PrintSubString(writer, bor, s, cur);
        }

        last_node_from_input = nodes_ptr[sh];
    }

    delete s;
    delete [] nodes_ptr;
    delete bor;
}

LZ78Archiver::~LZ78Archiver() {

}
