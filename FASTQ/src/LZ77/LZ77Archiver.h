#ifndef _LZ77_LZ77ARCHIVER_H_
#define _LZ77_LZ77ARCHIVER_H_

#include <utility>

#include "../interface/Archiver.h"

class LZ77Archiver : public Archiver {
public:
    LZ77Archiver();    
    void Compress(const char *input_file_name, const char *output_file_name);
    void Decompress(const char *input_file_name, const char *output_file_name);
    ~LZ77Archiver();
private:
    void push(int a1, int a2);
    std::pair<int, int> FindBestPrev(int index, int size);
    int WriteCompressed(int index, int length, int prev_index);

    static const int kBufferSize = 1 << 15;
    static const int kMaxLength = 100;

    char *data;
};

#endif // _LZ77_LZ77ARCHIVER_H_