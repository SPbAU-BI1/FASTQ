#include "LZ77Archiver.h"

#include <algorithm>

#include "../IO/BufferReader.h"
#include "../IO/BufferWriter.h"

LZ77Archiver::LZ77Archiver() {
    data_ = new char[kBufferSize];
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
    if (length == 0) {
        bw->put_bit(0);
        bw->put_char(data_[index]);
        length++;
    }
    else {
    	bw->put_short(length);
    	bw->put_short(prev_index);
    }
    return index + length - 1;
}

void LZ77Archiver::Compress(const char *input_file_name, const char *output_file_name) {
	BufferReader *br = new BufferReader(input_file_name);	
	BufferWriter *bw = new BufferWriter(output_file_name);
	int cur_position = 0;
	int first_not_compressed = 0;
	char c;
	while ((c = br->get_char()) != 0) {
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
	}
	while (first_not_compressed < cur_position) {
		auto result = FindBestPrev(first_not_compressed, cur_position);
		first_not_compressed = WriteCompressed(bw, first_not_compressed, result.first, result.second);
	}
	delete br;
	delete bw;	
}

void LZ77Archiver::Decompress(const char *input_file_name, const char *output_file_name) {

}

LZ77Archiver::~LZ77Archiver() {
    delete [] data_;
}