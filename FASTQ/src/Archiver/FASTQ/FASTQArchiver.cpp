#include "FASTQArchiver.h"
                    
#include "../LZ78/LZ78Archiver.h"
#include "../../InputOutput/Buffered/BufferedReader.h"
#include "../../InputOutput/Buffered/BufferedWriter.h"
#include "../../InputOutput/Bit/BitReader.h"
#include "../../InputOutput/Bit/BitWriter.h"
#include "../../InputOutput/StreamReader/StreamReader.h"
#include "../../InputOutput/ArrayReaderWriter/ArrayReaderWriter.h"

#include <stdio.h>

void FASTQArchiver::Compress(const char *input_file_name, const char *output_file_name) {
    BufferedWriter *compress_writer = new BufferedWriter(output_file_name); 
    fpos_t begin[kBlockSize], end[kBlockSize];
    compress_writer->setOffset(2 * kBlockSize * sizeof(fpos_t));

    for (int i = 0; i < kBlockSize; i++) {
        begin[i] = compress_writer->getOffset();
        Archiver *archiver = new LZ78Archiver();
        //compress_writer->PutShort((1 << 16) - 1);
        Reader *compress_reader = new StreamReader(input_file_name, kBlockSize, i);
        archiver->Compress(compress_reader, compress_writer);
        compress_writer->Flush();
        end[i] = compress_writer->getOffset();
        delete compress_reader; 
        delete archiver;
    }
    compress_writer->setOffset(0);
    for (int i = 0; i < kBlockSize; i++) {
        compress_writer->PutLong(begin[i]);
        compress_writer->PutLong(end[i]);
    }
    compress_writer->Flush();
    delete compress_writer;
}

void FASTQArchiver::Decompress(const char *input_file_name, const char *output_file_name) {
    BufferedReader *reader = new BufferedReader(input_file_name);    
    BufferedReader *readers[kBlockSize];
    Archiver *archivers[kBlockSize];
    ArrayReaderWriter *buffers[kBlockSize];
    
    fpos_t begin, end;
    for (int i = 0; i < kBlockSize; i++)
    {
        reader->GetLong((unsigned long long*) &begin);
        reader->GetLong((unsigned long long*) &end);
        readers[i] = new BufferedReader(input_file_name, begin, end);  
        archivers[i] = new LZ78Archiver();
        buffers[i] = new ArrayReaderWriter();
    } 
    delete reader;
    Writer *writer = new BufferedWriter(output_file_name);

    //decompresses a line from each uniform part and join it all together with help of cyclic array-buffer
    bool ended = 0;
    while (!ended) {
        for (int i = 0; i < kBlockSize; i++) {
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
    for (int i = 0; i < kBlockSize; i++) {
        delete readers[i];
        delete archivers[i];
        delete buffers[i];
    }
    delete writer;
}
