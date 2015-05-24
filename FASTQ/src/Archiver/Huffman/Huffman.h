#ifndef _HUFFMAN_ARCHIVER_H_
#define _HUFFMAN_ARCHIVER_H_

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
using std::string;

#include "../Interface/Archiver.h"

class Reader;
class Writer;

struct Node
{
    
    Node *l = NULL;
    Node *r = NULL;
    string value = "";
    int num = 0;    

};
                

class HuffmanArchiver : public Archiver
{ 

public:
    
    HuffmanArchiver();
    ~HuffmanArchiver();     
    void Compress(Reader *reader, Writer *writer);
    void Decompress(Reader *reader, Writer *writer);
    //bool PutNextCompressedPart(Reader *reader, Writer *writer);
    bool PutNextDecompressedPart(Reader *reader, Writer *writer);

private:
    
    void CompressInit(Reader *reader, Writer *writer);   
    void TreeSave(Node *v, unsigned short ParentNum, int Type);
    void TreeBuild(Reader *reader, Writer *writer);
    void Code(Node *a, string prefix);
    static bool comp(Node a, Node b);

	static const int kMaxNum = 10000;
    static const int kOpNum = 100;  
    static const int kCharNum = 256;    

    Node *root_;
    bool was_build_;
    unsigned short tree_num_;   	
    unsigned short sym_num_;   	
    int decompressed_index_;
    long long unsigned file_length_;  
    
	string code_[kCharNum];	
    Node tree_[kMaxNum];
    int num_[kCharNum];
    unsigned short parent_[kMaxNum];
    unsigned char type_[kMaxNum];
    bool is_sym_[kMaxNum];
    unsigned char sym_[kMaxNum];

};

#endif
