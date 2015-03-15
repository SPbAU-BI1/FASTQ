#include "LZ77Archiver.h"

#include <algorithm>

LZ77Archiver::LZ77Archiver() {
    data_ = new char[2 * kBufferSize + kMaxLength];
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

int LZ77Archiver::WriteCompressed(int index, int length, int prev_index) {
    if (length == 0) {
        //TODO (Nikitosh) push(0, data_[index]);
        length++;
    }
    else
        //TODO (Nikitosh) push(length, prev_index);
    return index + length - 1;
}

void LZ77Archiver::Compress(const char *input_file_name, const char *output_file_name) {
    FILE *input_file = fopen(input_file_name, "r");
    if (input_file == NULL) {
        //TODO (Nikitosh) exception
        fprintf(stderr, "There is no file %s\n", input_file_name);
        return;
    }

    int cur_position = 0; //begin position for compressing
    int read_position = 0; //begin position for reading in buffer
    int bytes_number = kBufferSize + kMaxLength; //number of bytes, that we want to read
    bool firstRead = true; 
    int first_not_compressed = 0;
    int last_not_compressed = 0;
    int read_bytes_number = 0; //number of successfully read bytes
    while ((read_bytes_number = fread(data_ + read_position, sizeof(char), bytes_number, input_file)) > 0) {
        for (int i = cur_position; i < read_position + read_bytes_number - kMaxLength; i++) { //
            auto result = FindBestPrev(i, read_position + read_bytes_number);
            i = WriteCompressed(i, result.first, result.second);  
        }
        first_not_compressed = std::max(0, read_position + read_bytes_number - kMaxLength);
        last_not_compressed = read_position + read_bytes_number;
        bytes_number = kBufferSize;
        read_position = kBufferSize + kMaxLength;
        cur_position = kBufferSize;
        if (!firstRead) {
            first_not_compressed -= kBufferSize;
            last_not_compressed -= kBufferSize;
            for (int i = 0; i < kBufferSize + kMaxLength; i++)
                data_[i] = data_[i + kBufferSize];
        }
        firstRead = 0;
    }
    //Compress remained part of file
    for (int i = first_not_compressed; i < last_not_compressed; i++) {
        auto result = FindBestPrev(i, last_not_compressed);
        i = WriteCompressed(i, result.first, result.second);  
    }
    fclose(input_file);
}

void LZ77Archiver::Decompress(const char *input_file_name, const char *output_file_name) {

}

LZ77Archiver::~LZ77Archiver() {
    delete [] data_;
}