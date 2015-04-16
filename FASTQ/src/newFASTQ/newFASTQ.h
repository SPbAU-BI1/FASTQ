#ifndef _NEWFASTQ_H_
#define _NEWFASTQ_H_


#include <utility>
#include <string>
#include "Archiver.h"


class BufferWriter;

class FASTQArchiver{
public:
    //FASTQArchiver();
    //std::string str[4] = {"_id_string","_fastq_string","_id_string_2","_quality_string"};
    int FileSize[4];  
    void Parse(const char *input_file_name);
    void Join(const char *output_file_name);
    //~FASTQArchiver();    

};







#endif 