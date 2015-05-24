inline bool BufferedReader::GetBit(bool *val) {
	return 0;
}

inline bool BufferedReader::GetChar(unsigned char *val) {
    if (in_buff_l_ == readen_size_) {
        Read();
        if (readen_size_ == 0) {
            return false;
        }
    }

    *val = in_buffer_[in_buff_l_++];
    
    return true;
}

inline bool BufferedReader::GetShort(unsigned short *val) {
    *val = 0;
    unsigned char val1, val2;

    if (!(GetChar(&val1) & GetChar(&val2))) {
        return false;
    }

    *val = (unsigned short) val1 + (unsigned short) val2 * (1 << 8);
    return true;
}

inline bool BufferedReader::GetInt(unsigned int *val) {
    *val = 0;
    unsigned short val1, val2;

    if (!(GetShort(&val1) & GetShort(&val2))) {
        return false;
    }

    *val = (unsigned int) val1 + (unsigned int) val2 * (1 << 16);
    return true;
}

inline bool BufferedReader::GetLong(unsigned long long *val) {
    *val = 0;
    unsigned int val1, val2;

    if (!(GetInt(&val1) & GetInt(&val2))) {
        return false;
    }

    *val = (unsigned long long) val1 + (unsigned long long) val2 * (1ll << 32);
    return true;
}

inline void BufferedReader::Read() {
    long long remaining_offset = end_offset_ - ftell(f_in_);
    readen_size_ = fread(in_buffer_, sizeof(char), std::min((long long) kBuffSize, remaining_offset), f_in_);
    in_buff_l_ = 0;
    
    if (ferror(f_in_)) {
        throw std::string("Could not read input file");
    }
}
