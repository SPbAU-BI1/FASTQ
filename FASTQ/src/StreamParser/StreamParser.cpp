#include "StreamParser.h"
#include "../IO/BufferReader.h"
#include "../IO/BufferWriter.h"

#include <algorithm>
#include <string>                         

void StreamParser::Parse(const char *input_file_name) {
    
    char** s = new char*[4];    
    for (int i = 0; i < 4; i++) {        
        s[i] = new char[100];     
    }
    for(int i = 0; i < 4; i++) {
        strcpy(s[i], input_file_name);
    }
    strcat(s[0], "_id_string");
    strcat(s[1], "_fastq_string");
    strcat(s[2], "_id_string_2");
    strcat(s[3], "_quality_string");  
                
    BufferReader *br = new BufferReader(input_file_name);   
    BufferWriter *bw[4];    
    for (int i = 0; i < 4; i++) {
        bw[i] = new BufferWriter(s[i]);
    }
    
    for (int i = 0; i < 4; i++) {        
        FileSize[i] = 0;     
    }
    unsigned char c;
    int num = 0;
    while (br->get_char(&c)) {
        bw[num]-> put_char(c);
        FileSize[num]++;
        if (c == '\n')   
            num = (num + 1) % 4;                              
    }

   // for(int i = 0; i < 4; i++) {        
      //  Compress(s[i]);               !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  //  }
                                           
    delete [] s;
    delete br; 
    delete [] bw;
}

void StreamParser::Join(const char *input_file_name) {
    
    char** s = new char*[5];    
    for (int i = 0; i < 5; i++) {    
        s[i] = new char[100];    
    }
    for(int i = 0; i < 5; i++) {
        strcpy(s[i], input_file_name);
    }
    strcat(s[0], "_id_string");
    strcat(s[1], "_fastq_string");
    strcat(s[2], "_id_string_2");
    strcat(s[3], "_quality_string");
    strcat(s[4], "_compressed");
    

    BufferReader *br[4]; 
    BufferWriter *bw = new BufferWriter(s[4]);
    for(int i = 0; i < 4; i++) {        
        br[i] = new BufferReader(s[i]);
    }              
      
    for (int i = 0; i < 4; i++) {        
        unsigned char c;
        while (br[i]->get_char(&c)) {
            bw->put_char(c);
        }
    }

    delete [] br;
    delete bw;

    for(int i = 0; i < 4; i++) {        
        remove(s[i]);
    }
    delete [] s;
    
}
