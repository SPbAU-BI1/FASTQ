#ifndef IO_BUFFERWRITER_H_
#define IO_BUFFERWRITER_H_

#include <stdio.h>
#include <string.h>

class BufferWriter {
public:
    BufferWriter(const char *output_file_name) {
        f_out_ = fopen(output_file_name, "wb");

        out_buffer_ = new char[kBuffSize];
        memset(out_buffer_, 0, kBuffSize);

        out_buff_l_ = 0;
    };

    inline void flush() {
        fwrite(out_buffer_, sizeof(char), (out_buff_l_ + 7) / 8, f_out_);
        memset(out_buffer_, 0, kBuffSize);
        out_buff_l_ = 0;
    };

    inline void put_bit(bool bit) {
        if (out_buff_l_ == kBuffSize * 8) {
            flush();
        }

        size_t index = out_buff_l_ / 8;
        size_t bit_num = out_buff_l_ % 8;
        out_buffer_[index] |= bit << bit_num;
        out_buff_l_++;
    };

    inline void put_char(char ch) {
        for (int i = 0; i < 8; i++) {
            put_bit(ch & (1 << i));
        }
    };

    inline void put_short(short sh) {
        put_char(sh & ((1 << 8) - 1));
        put_char(sh / (1 << 8));
    };

    ~BufferWriter() {
        flush();
        fclose(f_out_);
        delete out_buffer_;
    };

private:
    FILE *f_out_;
    char *out_buffer_;
    size_t out_buff_l_;
    const size_t kBuffSize = 1000;
};

#endif // IO_BUFFERWRITER_H_
