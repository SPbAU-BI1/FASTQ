#include "BufferedReader.h"

BufferedReader::BufferedReader(const char *input_file_name, long long begin_offset, long long end_offset): begin_offset_(begin_offset), 
                                                                                                     end_offset_(end_offset) {
    f_in_ = fopen(input_file_name, "rb");
    
    in_buffer_ = new char[kBuffSize];
    file_name_ = new char[strlen(input_file_name) + 1]();
    strcpy(file_name_, input_file_name);

    if (end_offset == std::numeric_limits<long long>::max()) {
        fseek(f_in_, 0, SEEK_END);
        end_offset_ = ftell(f_in_);
    }
    
    fseek(f_in_, begin_offset_, SEEK_SET);
    readen_size_ = 0;
    in_buff_l_ = 0;
}

BufferedReader::BufferedReader(const BufferedReader &reader) {
    BufferedReader(reader.file_name_, reader.begin_offset_, reader.end_offset_);
    fseek(f_in_, ftell(reader.f_in_), SEEK_SET); 
}

Reader* BufferedReader::Clone() {
	return new BufferedReader(*this);	
}

BufferedReader::~BufferedReader() {
    fclose(f_in_);
    delete [] in_buffer_;
    delete [] file_name_;
}
