#ifndef LZ78_LZ78ARCHIVER_H_
#define LZ78_LZ78ARCHIVER_H_

#include "../interface/Archiver.h"
#include <utility>
#include "Bor.h"
#include "../IO/BufferReader.h"
#include "../IO/BufferWriter.h"

class LZ78Archiver : public Archiver {
private:
    char PrintSubString(BufferWriter *bw, Bor *bor, char *s, BorNode *cur);
public:
    LZ78Archiver();
    void Compress(const char *input_file_name, const char *output_file_name);
    void Decompress(const char *input_file_name, const char *output_file_name);
    ~LZ78Archiver();
};

#endif // LZ78_LZ78ARCHIVER_H_
