#include "ArrayReaderWriter.h"

ArrayReaderWriter::ArrayReaderWriter(): read_position_(0), write_position_(0) {
    data_ = new unsigned char[kBufferSize];
}

void ArrayReaderWriter::CorrectPosition(int &position) {
    if (position >= kBufferSize)
        position -= kBufferSize;
}

bool ArrayReaderWriter::GetChar(unsigned char *ch) {
    if (read_position_ == write_position_)
        return 0;
    *ch = data_[read_position_++];
    CorrectPosition(read_position_);
    return 1;
}

bool ArrayReaderWriter::GetShort(unsigned short *sh) {
    if (read_position_ == write_position_)
        return 0;
    *sh = data_[read_position_++];
    CorrectPosition(read_position_);
    if (read_position_ == write_position_)
        return 0;
    *sh += (1 << 8) * (unsigned short) data_[read_position_++];
    CorrectPosition(read_position_);
    return 1;
}

void ArrayReaderWriter::PutChar(unsigned char ch) {
    data_[write_position_++] = ch;
    CorrectPosition(write_position_);
}

void ArrayReaderWriter::PutShort(unsigned short sh) {
    data_[write_position_++] = sh % (1 << 8);
    CorrectPosition(write_position_);
    data_[write_position_++] = sh / (1 << 8);
    CorrectPosition(write_position_);
}

void ArrayReaderWriter::Flush() {}

ArrayReaderWriter::~ArrayReaderWriter()
{
    delete data_;
}
