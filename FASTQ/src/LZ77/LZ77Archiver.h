#ifndef _LZ77_LZ77ARCHIVER_H_
#define _LZ77_LZ77ARCHIVER_H_

#include "../interface/Archiver.h"

class LZ77Archiver : public Archiver {
public:
    LZ77Archiver();
    void Compress(const char *input_file_name, const char *output_file_name);
    void Decompress(const char *input_file_name, const char *output_file_name);
    ~LZ77Archiver();
};

#endif // _LZ77_LZ77ARCHIVER_H_