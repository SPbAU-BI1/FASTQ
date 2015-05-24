#include "ArrayReaderWriter.h"

#include <stdio.h>

ArrayReaderWriter::ArrayReaderWriter(): read_position_(0), write_position_(0) {
    data_ = new unsigned char[kBufferSize]();
}

ArrayReaderWriter::ArrayReaderWriter(const ArrayReaderWriter& arrayReaderWriter) {
    data_ = new unsigned char[kBufferSize]();
    for (int i = 0; i < kBufferSize; i++)
        data_[i] = arrayReaderWriter.data_[i];
    read_position_ = arrayReaderWriter.read_position_;
    write_position_ = arrayReaderWriter.write_position_;
}

ArrayReaderWriter* ArrayReaderWriter::Clone() {
    return new ArrayReaderWriter(*this);
}

void ArrayReaderWriter::Flush() {}

bool ArrayReaderWriter::SearchLineFeed() {
    int cur_read_position = read_position_;
    while (cur_read_position != write_position_) {
        if (data_[cur_read_position] == '\n')
            return 1;
        CorrectPosition(++cur_read_position);
    }
    return 0;
}

void ArrayReaderWriter::PutNextLine(Writer *writer) {
    int cur_read_position = read_position_;
    unsigned char ch = 0;
    while (cur_read_position != write_position_ && data_[cur_read_position] != '\n') {
        GetChar(&ch);
        writer->PutChar(ch);
        CorrectPosition(++cur_read_position);
    }
    
    if (cur_read_position != write_position_)
    {
        GetChar(&ch);
        writer->PutChar(ch);
    }
}

ArrayReaderWriter::~ArrayReaderWriter() {
    delete [] data_;
}
