inline void BufferedWriter::Flush() {
    fwrite(out_buffer_, sizeof(char), out_buff_l_, f_out_);
    out_buff_l_ = 0;
}

inline void BufferedWriter::PutChar(unsigned char val) {
    if (out_buff_l_ == kBuffSize) {
        Flush();
    }

    out_buffer_[out_buff_l_++] = val;
}

inline void BufferedWriter::PutShort(unsigned short val) {
    PutChar(val & ((1 << 8) - 1));
    PutChar(val >> 8);
}

inline void BufferedWriter::PutInt(unsigned int val) {
    PutShort(val & ((1 << 16) - 1));
    PutShort(val >> 16);
}

inline void BufferedWriter::PutLong(unsigned long long val) {
    PutInt(val & ((1ll << 32) - 1));
    PutInt(val >> 32);
}

inline void BufferedWriter::setOffset(long long offset)
{
    Flush();
    fseek(f_out_, offset, SEEK_SET);
}

inline long long BufferedWriter::getOffset()
{
    Flush();
    return ftell(f_out_);
}
