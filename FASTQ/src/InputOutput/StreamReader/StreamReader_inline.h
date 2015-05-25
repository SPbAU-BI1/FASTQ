#include <string.h>

inline bool StreamReader::GetBit(bool*) {
    return 0;
}

inline bool StreamReader::GetChar(unsigned char *val) {
    if (cur_position_ == cur_length_) {
        int read_row_count = block_size_;
        if (cur_length_ == -1)                      
            read_row_count = row_number_ + 1;
        //Reads block of unnecessary lines
        for (int i = 0; i < read_row_count; i++)
            if (fgets(buffer_, kBufferSize - 1, f_in_) == NULL)
                return 0;
        cur_position_ = 0;
        cur_length_ = strlen(buffer_);
    }
    *val = buffer_[cur_position_++];
    //fprintf(stderr, "c%cd\n", *val);
    return 1;   
}

inline bool StreamReader::GetShort(unsigned short *val) {
    unsigned char val1 = 0, val2 = 0;
    if (!GetChar(&val1))
        return 0;
    if (!GetChar(&val2))
        return 0;
    *val = val1 * (1 << 8) + val2;
    return 1;
}

inline bool StreamReader::GetInt(unsigned int *val) {
    unsigned short val1 = 0, val2 = 0;
    if (!GetShort(&val1))
        return 0;
    if (!GetShort(&val2))
        return 0;
    *val = val1 * (1 << 16) + val2;
    return 1;
}

inline bool StreamReader::GetLong(unsigned long long *val) {
    unsigned int val1 = 0, val2 = 0;
    if (!GetInt(&val1))
        return 0;
    if (!GetInt(&val2))
        return 0;
    *val = val1 * (1ll << 32) + val2;
    return 1;
}
