#include "StreamParser.h"

#include <algorithm>
#include <string>                         

#include "../Interface/Reader.h"
#include "../Interface/Writer.h"
#include "../Buffered/BufferedReader.h"
#include "../Buffered/BufferedWriter.h"

std::vector <char*> StreamParser::Parse(const char *input_file_name) {
    
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
                
    BufferedReader *br = new BufferedReader(input_file_name);   
    BufferedWriter *bw[4];    
    for (int i = 0; i < 4; i++) {
        bw[i] = new BufferedWriter(s[i]);
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

    std::vector <char*> result;
    for(int i = 0; i < 4; i++) {        
        result.push_back(s[i]);
    }
                                           
    delete [] s;
    delete br;
    for (int i = 0; i < 4; i++)
        delete bw[i]; 
    return result;
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
    

    BufferedReader *br[4]; 
    BufferedWriter *bw = new BufferedWriter(s[4]);
    for(int i = 0; i < 4; i++) {        
        br[i] = new BufferedReader(s[i]);
    }              
      
    for (int i = 0; i < 4; i++) {        
        unsigned char c;
        while (br[i]->get_char(&c)) {
            bw->put_char(c);
        }
    }

    for (int i = 0; i < 4; i++)
        delete br[i]; 
    delete bw;

    for(int i = 0; i < 4; i++) {        
        remove(s[i]);
    }
    delete [] s;
    
}
