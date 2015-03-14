#ifndef LZ78_LZ77ARCHIVER_H_
#define LZ78_LZ77ARCHIVER_H_

#include "../interface/Archiver.h"

class LZ78Archiver : public Archiver {
public:
    LZ78Archiver();
    void Compress(const char *input_file_name, const char *output_file_name);
    void Decompress(const char *input_file_name, const char *output_file_name);
    ~LZ78Archiver();
};

#endif // LZ78_LZ77ARCHIVER_H_
