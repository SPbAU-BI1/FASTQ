//Archiver of FASTQ file. 
//Compress: Splits file in 4 uniform parts and compressed separately
//Decompress: Decompresses 4 parts and join it together

#ifndef _FASTQARCHIVER_H_
#define _FASTQARCHIVER_H_

class Reader;
class Writer;

class FASTQArchiver {
public:
    void Compress(const char *input_file_name, const char *output_file_name);
    void Decompress(const char *input_file_name, const char *output_file_name);
private:
    static const int kBlockSize = 4; //number of uniform parts of data
};

#endif //_FASTQARCHIVER_H_