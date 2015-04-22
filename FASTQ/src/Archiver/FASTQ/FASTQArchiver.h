#ifndef _FASTQARCHIVER_H_
#define _FASTQARCHIVER_H_

class Reader;
class Writer;

class FASTQArchiver {
public:
    void Compress(const char *input_file_name, const char *output_file_name);
    void Decompress(const char *input_file_name, const char *output_file_name);
private:
    static const int block_size_ = 4;
};

#endif //_FASTQARCHIVER_H_