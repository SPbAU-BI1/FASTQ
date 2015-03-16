//Compress and Decompress text file with LZ77 algorithm

#ifndef LZ77_LZ77ARCHIVER_H_
#define LZ77_LZ77ARCHIVER_H_

#include <utility>

#include "../interface/Archiver.h"

class BufferWriter;

class LZ77Archiver : public Archiver {
public:
    LZ77Archiver();    
    void Compress(const char *input_file_name, const char *output_file_name);
    void Decompress(const char *input_file_name, const char *output_file_name);
    ~LZ77Archiver();
private:
    //Finds length and position of maximal block earlier identical with block, beginning with index.  
    std::pair<int, int> FindBestPrev(int index, int size);
    //Writes compressed block beginning with index and returns index of first not compressed symbol.
    int WriteCompressed(BufferWriter *bw, int index, int length, int prev_index);

    //Size of sliding window.
    static const int kWindowSize = 1 << 15;
    //Size of maximal length, that could be compressed.
    static const int kMaxLength = 100;
	//Size of buffer
	static const int kBufferSize = 2 * kWindowSize + kMaxLength;

    //Data array, obtained from input file.
    char *data_;
};

#endif // LZ77_LZ77ARCHIVER_H_