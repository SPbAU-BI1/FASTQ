#include "FASTQArchiver.h"

#include "../LZ78/LZ78Archiver.h"
#include "../../InputOutput/Buffered/BufferedReader.h"
#include "../../InputOutput/Buffered/BufferedWriter.h"
#include "../../InputOutput/StreamReader/StreamReader.h"
#include "../../InputOutput/ArrayReaderWriter/ArrayReaderWriter.h"

void FASTQArchiver::Compress(const char *input_file_name, const char *output_file_name) {
    Archiver *archiver = new LZ78Archiver();
    Writer *compress_writer = new BufferedWriter(output_file_name); 
    for (int i = 0; i < block_size_; i++) {
        compress_writer->PutChar(255);
        compress_writer->PutChar(255);
        Reader *compress_reader = new StreamReader(input_file_name, block_size_, i);
        archiver->Compress(compress_reader, compress_writer);
        delete compress_reader; 
    }
}

void FASTQArchiver::Decompress(const char *input_file_name, const char *output_file_name) {
    //Doesn't work now. TODO
    /*
    BufferedReader *readers[block_size_];
    unsigned char last[block_size_], nearly_last[block_size_];
    for (int i = 0; i < block_size_; i++) {
        readers[i] = new BufferedReader(input_file_name);  
        last[i] = 0;
        nearly_last[i] = 0;
    }
    int first_not_used = 0;
    while (1) {
        for (int i = first_not_used; i < block_size_; i++) {
            nearly_last[i] = last[i];
            readers[i]->GetChar(&last[i]);
        } 
        if (last[first_not_used] == 255 && nearly_last[first_not_used] == 255)
            first_not_used++;
        if (first_not_used == block_size_)
            break; 
    }
    Archiver *archivers[block_size_];
    ArrayReaderWriter *buffers[block_size_];
    for (int i = 0; i < block_size_; i++) {
        archivers[i] = new LZ78Archiver();
        buffers[i] = new ArrayReaderWriter();
    }
    while (1) {
        for (int i = 0; i < block_size_; i++) {
            archivers[i]->PutNextDecompressedPart(readers[i], buffers[i]);
        
        }
    }
    */
}
