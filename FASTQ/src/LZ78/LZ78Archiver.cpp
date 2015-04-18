#include "LZ78Archiver.h"

LZ78Archiver::LZ78Archiver() {

}

char LZ78Archiver::PrintSubString(BufferWriter *bw, Bor *bor, char *s, BorNode *cur) {
    size_t top = 0;

    while (cur != bor->get_root()) {
        s[top++] = cur->get_symbol();
        cur = cur->get_father();
    }

    for (int i = (int)top - 1; i >= 0; i--) {
        bw->put_char(s[i]);
    }

    return s[top - 1];
}

void LZ78Archiver::Compress(const char *input_file_name, const char *output_file_name) {
    BufferReader *br = new BufferReader(input_file_name);
    BufferWriter *bw = new BufferWriter(output_file_name);

    Bor *bor = new Bor();

    unsigned char ch;
    std::pair<bool, size_t> res;

    while (br->get_char(&ch)) {
        res = bor->add_node((char)ch);
        if (res.first) {
            bw->put_short((short)res.second);
        }
    }

    bw->put_short((short)bor->get_cur_id());

    delete bor;
    delete br;
    delete bw;
}

void LZ78Archiver::Decompress(const char *input_file_name, const char *output_file_name) {
    BufferReader *br = new BufferReader(input_file_name);
    BufferWriter *bw = new BufferWriter(output_file_name);

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

    while (br->get_short(&sh)) {
        printed = false;

        if (sh != bor->size() + 1) {
            cur = nodes_ptr[sh];
            last_char = PrintSubString(bw, bor, s, cur);
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
            last_char = PrintSubString(bw, bor, s, cur);
        }

        last_node_from_input = nodes_ptr[sh];
    }

    delete s;
    delete [] nodes_ptr;
    delete bor;
    delete bw;
    delete br;
}

LZ78Archiver::~LZ78Archiver() {

}
