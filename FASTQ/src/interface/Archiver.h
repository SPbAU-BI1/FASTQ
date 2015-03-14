#ifndef _INTERFACE_ARCHIVER_H_
#define _INTERFACE_ARCHIVER_H_

#include <cstdio>

class Archiver {
public:
    virtual void Compress(const char *input_file_name, const char *output_file_name) = 0;
    virtual void Decompress(const char *input_file_name, const char *output_file_name) = 0;
};

#endif // _INTERFACE_ARCHIVER_H_