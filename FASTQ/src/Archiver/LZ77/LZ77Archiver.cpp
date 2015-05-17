#include "LZ77Archiver.h"

#include <algorithm>

#include "../../InputOutput/Interface/Reader.h"
#include "../../InputOutput/Interface/Writer.h"

LZ77Archiver::LZ77Archiver() {
    data_ = new unsigned char[kBufferSize]();
}

//Returns a pair <maximum length of repeating part, shift to this part from current position>
std::pair <int, int> LZ77Archiver::FindBestPrev(int index, int size)
{
    int max_length = 0;
    int optimal_dist = 0;
    for (int j = std::max(0, index - kWindowSize); j < index; j++) {
        int max_cur_length = kMaxLength;
        for (int g = 0; g < kMaxLength; g++) {
            if (index + g == size || data_[index + g] != data_[j + g]) {
                max_cur_length = g;
                break;
            }   
        } 
        if (max_length < max_cur_length) {
            max_length = max_cur_length;
            optimal_dist = index - j;
        }
    }
    return std::make_pair(max_length, optimal_dist);
}

//Writes either 0-bit and char or a pair <length, shift>
int LZ77Archiver::WriteCompressed(Writer *writer, int index, int length, int prev_index) {
    if (length < 3) {
        writer->PutChar(0);
        writer->PutChar(data_[index]);
        length = 1;
    }
    else {
        writer->PutChar(1);
        writer->PutShort(length);
        writer->PutShort(prev_index);
    }
    return index + length;
}

void LZ77Archiver::Compress(Reader *reader, Writer *writer) {
    int cur_position = 0;
    int first_not_compressed = 0;
    unsigned char c;

    while (reader->GetChar(&c)) {
        data_[cur_position++] = c;
        //Moves current data to begin if end of sliding window occured
        if (cur_position == kBufferSize) {
            int last_useful = first_not_compressed - kWindowSize;
            for (int i = last_useful; i < cur_position; i++)
                data_[i - (last_useful)] = data_[i];
            cur_position -= last_useful;
            first_not_compressed -= last_useful;
        }
        //Finds best option to compress              
        if (cur_position - first_not_compressed >= kMaxLength) {
            auto result = FindBestPrev(first_not_compressed, cur_position);
            first_not_compressed = WriteCompressed(writer, first_not_compressed, result.first, result.second);
        }
    }
    //Compresses remaining data 
    while (first_not_compressed < cur_position) {
        auto result = FindBestPrev(first_not_compressed, cur_position);
        first_not_compressed = WriteCompressed(writer, first_not_compressed, result.first, result.second);
    }
    writer->PutChar(1);
    writer->PutShort(0);
}

void LZ77Archiver::Decompress(Reader *reader, Writer *writer) {
    unsigned char type;
    int cur_position = 0;
    while(reader->GetChar(&type)) {
        //Option of char
        if (type == 0) {
            reader->GetChar(&data_[cur_position]);
            writer->PutChar(data_[cur_position++]);
        }
        //Option of pair <length, shift>
        else {
            unsigned short length = 0, prev_index = 0;
            reader->GetShort(&length);
            if (length == 0)
                break;
            reader->GetShort(&prev_index);
            int last_element = cur_position - prev_index + length;
            for (int i = cur_position - prev_index; i < last_element; i++)
            {
                data_[cur_position] = data_[i];
                writer->PutChar(data_[cur_position++]);
            }
        }
        //Moves current data to begin if end of sliding window occured
        if (cur_position > kBufferSize - kMaxLength) {
            int last_useful = cur_position - kWindowSize;
            for (int i = last_useful; i < cur_position; i++)
                data_[i - last_useful] = data_[i];
            cur_position -= last_useful;
        }
    }
}

LZ77Archiver::~LZ77Archiver() {
    delete [] data_;
}