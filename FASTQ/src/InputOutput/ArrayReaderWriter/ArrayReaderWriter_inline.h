inline void ArrayReaderWriter::CorrectPosition(int &position) {
    if (position >= kBufferSize)
        position -= kBufferSize;
}

inline bool ArrayReaderWriter::GetBit(bool *val) {
	return 0;
}

inline bool ArrayReaderWriter::GetChar(unsigned char *val) {
    if (read_position_ == write_position_)
        return 0;
    *val = data_[read_position_++];
    CorrectPosition(read_position_);
    return 1;
}

inline bool ArrayReaderWriter::GetShort(unsigned short *val) {
    if (read_position_ == write_position_)
        return 0;
    *val = data_[read_position_++];
    CorrectPosition(read_position_);
    if (read_position_ == write_position_)
        return 0;
    *val += (1 << 8) * (unsigned short) data_[read_position_++];
    CorrectPosition(read_position_);
    return 1;
}

inline bool ArrayReaderWriter::GetInt(unsigned int *val) {
    unsigned short val1, val2;
    if (!GetShort(&val1))
        return 0;
    if (!GetShort(&val2))
        return 0;
    *val = val2 * (1 << 16) + val1;
    return 1;
}

inline bool ArrayReaderWriter::GetLong(unsigned long long *val) {
    unsigned int val1, val2;
    if (!GetInt(&val1))
        return 0;
    if (!GetInt(&val2))
        return 0;
    *val = val2 * (1ll << 32) + val1;
    return 1;
}

inline void ArrayReaderWriter::PutBit(bool val) {}

inline void ArrayReaderWriter::PutChar(unsigned char val) {
    data_[write_position_++] = val;
    CorrectPosition(write_position_);
}

inline void ArrayReaderWriter::PutShort(unsigned short val) {
    data_[write_position_++] = val & ((1 << 8) - 1);
    CorrectPosition(write_position_);
    data_[write_position_++] = val >> 8;
    CorrectPosition(write_position_);
}

inline void ArrayReaderWriter::PutInt(unsigned int val) {
    PutShort(val & ((1 << 16) - 1));
    PutShort(val >> 16);
}

inline void ArrayReaderWriter::PutLong(unsigned long long val) {
    PutInt(val & ((1ll << 32) - 1));
    PutInt(val >> 32);
}
