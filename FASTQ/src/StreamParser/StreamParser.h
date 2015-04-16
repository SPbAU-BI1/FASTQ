#ifndef _STREAMPARSER_H_
#define _STREAMPARSER_H_

#include <utility>
#include <string>
#include "../Interface/Archiver.h"

class BufferWriter;

class StreamParser{
public:
    //std::string str[4] = {"_id_string","_fastq_string","_id_string_2","_quality_string"};
    int FileSize[4];  
    void Parse(const char *input_file_name);
    void Join(const char *output_file_name);
};

#endif //_STREAMPARSER_H_