#include "FASTQArchiver.h"
                    
#include "../LZ78/LZ78Archiver.h"
#include "../../InputOutput/Buffered/BufferedReader.h"
#include "../../InputOutput/Buffered/BufferedWriter.h"
#include "../../InputOutput/StreamReader/StreamReader.h"
#include "../../InputOutput/ArrayReaderWriter/ArrayReaderWriter.h"

#include <stdio.h>

void FASTQArchiver::Compress(const char *input_file_name, const char *output_file_name) {
    Writer *compress_writer = new BufferedWriter(output_file_name); 
    for (int i = 0; i < block_size_; i++) {
        //Next two chars signalize about beginning of new part
        //It's bad solution
        //TODO: something with fseek() and ftell() functions
        Archiver *archiver = new LZ78Archiver();
        compress_writer->PutShort((1 << 16) - 1);
        Reader *compress_reader = new StreamReader(input_file_name, block_size_, i);
        archiver->Compress(compress_reader, compress_writer);
        compress_writer->Flush();
        delete compress_reader; 
        delete archiver;
    }
    //delete archiver;
    delete compress_writer;
}

void FASTQArchiver::Decompress(const char *input_file_name, const char *output_file_name) {
    BufferedReader *readers[block_size_];
    unsigned short last[block_size_];
    for (int i = 0; i < block_size_; i++) {
        readers[i] = new BufferedReader(input_file_name);  
        last[i] = 0;
    }

    //splits into block_size_ parts of uniform data
    int first_not_used = 0;
    while (1) {
        for (int i = first_not_used; i < block_size_; i++)
            readers[i]->GetShort(&last[i]);
        if (last[first_not_used] == ((1 << 16) - 1))
        {
            first_not_used++;
            for (int i = first_not_used; i < block_size_; i++)
                last[i] = 0;
        }
        if (first_not_used == block_size_)
            break; 
    }

    Archiver *archivers[block_size_];
    ArrayReaderWriter *buffers[block_size_];
    for (int i = 0; i < block_size_; i++) {
        archivers[i] = new LZ78Archiver();
        buffers[i] = new ArrayReaderWriter();
    }
    Writer *writer = new BufferedWriter(output_file_name);
    
    //decompresses a line from each uniform part and join it all together with help of cyclic array-buffer
    bool ended = 0;
    while (!ended) {
        for (int i = 0; i < block_size_; i++) {
            while (!(buffers[i]->SearchLineFeed()))
                if (!archivers[i]->PutNextDecompressedPart(readers[i], buffers[i])) {
                    ended = 1;
                    break;
                }
            if (!ended)           
                buffers[i]->PutNextLine(writer);        
        }
    }
    
    writer->Flush();
    for (int i = 0; i < block_size_; i++) {
        delete readers[i];
        delete archivers[i];
        delete buffers[i];
    }
    delete writer;
}
