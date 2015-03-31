#include "LZ77Archiver.h"

#include <iostream>
#include <algorithm>

#include "../IO/BufferReader.h"
#include "../IO/BufferWriter.h"

LZ77Archiver::LZ77Archiver() {
    data_ = new unsigned char[kBufferSize]();
}

std::pair <int, int> LZ77Archiver::FindBestPrev(int index, int size)
{
    int max_length = 0;
    int optimal_dist = 0;
    for (int j = std::max(0, index - kBufferSize); j < index; j++)
        for (int g = 0; g < kMaxLength; g++) {
            if (index + g == size || data_[index + g] != data_[j + g]) {
                if (max_length < g) {
                    max_length = g;
                    optimal_dist = index - j;
                }
                break;
            }   
        } 
    return std::make_pair(max_length, optimal_dist);
}

int LZ77Archiver::WriteCompressed(BufferWriter *bw, int index, int length, int prev_index) {
    if (length < 6) {
        bw->put_bit(0);
        bw->put_char(data_[index]);
        length = 1;
    }
    else {
        bw->put_bit(1);
        bw->put_short(length);
        bw->put_short(prev_index);
    }
    return index + length;
}

void LZ77Archiver::Compress(const char *input_file_name, const char *output_file_name) {
    BufferReader *br = new BufferReader(input_file_name);   
    BufferWriter *bw = new BufferWriter(output_file_name);
    int cur_position = 0;
    int first_not_compressed = 0;
    unsigned char c;
    while (br->get_char(&c)) {
        data_[cur_position++] = c;
        if (cur_position == kBufferSize) {
            int last_useful = first_not_compressed - kWindowSize;
            for (int i = last_useful; i < cur_position; i++)
                data_[i - (last_useful)] = data_[i];
            cur_position -= last_useful;
            first_not_compressed -= last_useful;
        }                                      
        if (cur_position - first_not_compressed >= kMaxLength) {
            auto result = FindBestPrev(first_not_compressed, cur_position);
            first_not_compressed = WriteCompressed(bw, first_not_compressed, result.first, result.second);
        }
        //std::cerr << cur_position << " " << std::endl;
    }
    while (first_not_compressed < cur_position) {
        auto result = FindBestPrev(first_not_compressed, cur_position);
        first_not_compressed = WriteCompressed(bw, first_not_compressed, result.first, result.second);
    }
    bw->put_bit(1);
    bw->put_short(0);
    delete br;
    delete bw;  
}

void LZ77Archiver::Decompress(const char *input_file_name, const char *output_file_name) {
    BufferReader *br = new BufferReader(input_file_name);   
    BufferWriter *bw = new BufferWriter(output_file_name);
    bool type;
    int cur_position = 0;
    while(br->get_bit(&type)) {
        if (type == 0) {
            br->get_char(&data_[cur_position]);
            bw->put_char(data_[cur_position++]);
        }
        else {
            unsigned short length = 0, prev_index = 0;
            br->get_short(&length);
            if (length == 0)
            	break;
            br->get_short(&prev_index);
            int last_element = cur_position - prev_index + length;
            for (int i = cur_position - prev_index; i < last_element; i++)
            {
                data_[cur_position] = data_[i];
                bw->put_char(data_[cur_position++]);
            }
        }
        if (cur_position > kBufferSize - kMaxLength)
        {
            int last_useful = cur_position - kWindowSize;
            for (int i = last_useful; i < cur_position; i++)
                data_[i - last_useful] = data_[i];
            cur_position -= last_useful;
        }
    }
    delete br;
    delete bw;
}

LZ77Archiver::~LZ77Archiver() {
    delete [] data_;
}