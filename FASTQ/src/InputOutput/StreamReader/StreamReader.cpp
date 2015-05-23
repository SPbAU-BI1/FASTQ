#include "StreamReader.h"

#include <string.h>

StreamReader::StreamReader(const char *input_file_name, int block_size, int row_number): block_size_(block_size), 
                                                                                         row_number_(row_number), 
                                                                                         cur_position_(-1), 
                                                                                         cur_length_(-1) {
    f_in_ = fopen(input_file_name, "r");
	file_name_ = new char[strlen(input_file_name) + 1]();
    strcpy(file_name_, input_file_name);
    buffer_ = new char[kBufferSize]();
}

StreamReader::StreamReader(const StreamReader &reader) {
	StreamReader(reader.file_name_, reader.block_size_, reader.row_number_);
	cur_position_ = reader.cur_position_;
	cur_length_ = reader.cur_length_;
}

Reader* StreamReader::Clone() {
	return new StreamReader(*this);	
}

StreamReader::~StreamReader() {
    fclose(f_in_);
    delete [] buffer_;
	delete [] file_name_;
}