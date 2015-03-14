#ifndef LZ78_PRINTWRITER_H_
#define LZ78_PRINTWRITER_H_

#include <stdio.h>
#include <stdlib.h>

class PrintWriter {
private:
    FILE *f_in_, *f_out_;
    char *in_buffer_, *out_buffer_;
    size_t in_buff_l_, out_buff_l_, readen_size_;
    const size_t buff_size_ = 1000;
public:
    PrintWriter(const char* input_file_name, const char* output_file_name);

    char get_next_char();
    void put_next_char(char ch);
    void flush();

    ~PrintWriter();
};

#endif // LZ78_PRINTWRITER_H_
