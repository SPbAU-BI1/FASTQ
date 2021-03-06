#include "HuffmanArchiver.h"
#include "../../InputOutput/Interface/Reader.h"
#include "../../InputOutput/Interface/Writer.h"


HuffmanArchiver::HuffmanArchiver()
{
    for(int i = 0; i < kCharNum; i++)
        code_[i] = "xx";
    for(int i = 0; i < kMaxNum; i++)
        sym_[i] = 'x';
    root_ = NULL;
    was_build_ = false;
    tree_num_ = 0; 
    sym_num_ = 0;     
    decompressed_index_ = 0;
}
HuffmanArchiver::~HuffmanArchiver(){}

bool HuffmanArchiver::comp(Node a, Node b)
{
    return (a.num > b.num);
}

void HuffmanArchiver::TreeSave(Node *v, unsigned short ParentNum, int type)
{
    parent_[tree_num_] = ParentNum;
    type_[tree_num_] = (unsigned char) (char) type;
    tree_num_++;  
    int x = tree_num_ - 1;
    
    if (v->value.length() > 1)
    {
        TreeSave(v->l, x, 0); 
        TreeSave(v->r, x, 1);    
    } 
    else
    {
        is_sym_[x] = true;  
        sym_[x] = (unsigned char) v->value[0];
    }    

}

void HuffmanArchiver::Code(Node *a, string prefix)
{    
    if (a->value.length() == 1)
    {
        code_[(int) a->value[0]] = prefix;      
        return;
    }
    Code(a->l, prefix + "0");   
    Code(a->r, prefix + "1");                            

}
void HuffmanArchiver::CompressInit(Reader *reader)
{    
    unsigned char sym;
    file_length_ = 0;
    for (int i = 0; i < kCharNum; i++)
        num_[i] = 0;
    while (reader->GetChar(&sym))
    {
        file_length_++;
        num_[(int) sym]++;    
    }   

}
void HuffmanArchiver::Compress(Reader *reader, Writer *writer)
{    
    unsigned short n = 0;
    long long sym_to_read = 0;
    unsigned char sym;
    Node comp_tree[kMaxNum];
    Reader *newreader = reader->Clone();
    CompressInit(reader);                           
    
    for(int i = 0; i < kCharNum; i++)
        if (num_[i] > 0)
        {
            comp_tree[n].value = char(i);         
            comp_tree[n].num = num_[i];    
            n++;                        
        } 
    sym_num_ = n; 
    std::sort(comp_tree, comp_tree + n, comp);    
    while (n > 1)
    {
        Node *n1 = new Node;
        Node *n2 = new Node;
        *n1 = comp_tree[n-2];       
        *n2 = comp_tree[n-1];        
        n--;
        comp_tree[n-1].l = n1;
        comp_tree[n-1].r = n2;
        comp_tree[n-1].value = n1->value + n2->value;
        comp_tree[n-1].num = n1->num + n2->num;
        std::sort(comp_tree, comp_tree + n, comp);
    }
    root_ = &comp_tree[0];    
    Code(root_, "");
    for(int i = 0; i < kCharNum; i++)
        if (num_[i] > 0)
            sym_to_read += num_[i] * code_[i].length();

    for (int i = 0; i < kMaxNum; i++)
        is_sym_[i] = false;
    tree_num_ = 0;    
    TreeSave(root_, 0, 0);
    
    writer->PutShort(tree_num_);    
    for(int i = 0; i < tree_num_; i++)
    {
        writer->PutShort(parent_[i]);
        writer->PutChar(type_[i]);                      
    } 
    writer->PutShort(sym_num_);    
    for(unsigned short i = 0; i < tree_num_; i++)
    {
        if (is_sym_[i])
        {
            writer->PutShort(i);
            writer->PutChar(sym_[i]);
        }    
    }
    
    writer->PutLong(sym_to_read);                           
    writer->Flush();
    
    while(newreader->GetChar(&sym))
    {       
        int k = int(sym);
        for(size_t j = 0; j < code_[k].length(); j++)
            if (code_[k][j] == '0')
                writer->PutBit(false);                      
            else    
                writer->PutBit(true);                               
    }
    
    writer->Flush();   
}

void HuffmanArchiver::Decompress(Reader *reader, Writer *writer)
{   
    while (PutNextDecompressedPart(reader,writer)); 
}

bool HuffmanArchiver::PutNextDecompressedPart(Reader *reader, Writer *writer)
{
    if (!was_build_)
    {
        TreeBuild(reader);
        was_build_ = true;  
        reader->GetLong(&file_length_);
    }                             
    if (decompressed_index_ == file_length_)   
        return 0;
    int read_num = 0;
    bool b; 
    Node *cur_node;
    cur_node = &tree_[0];
    while(read_num <= kOpNum && decompressed_index_ < file_length_ && reader->GetBit(&b))
    {    
        decompressed_index_++;
        if (!b)
            cur_node = cur_node->l;
        else
           cur_node = cur_node->r;
        if (cur_node->value.length() == 1)
        {
            read_num++;         
            writer->PutChar(cur_node->value[0]);            
            cur_node = &tree_[0];            
        }
    } 
    writer->Flush();    
    return 1;
}


void HuffmanArchiver::TreeBuild(Reader *reader)
{
    unsigned char type,sym;
    unsigned short num;    
    unsigned short sym_num;

    reader->GetShort(&tree_num_);        
    tree_[0].value = "xx"; 
    reader->GetShort(&num);
    reader->GetChar(&type);

    for(int i = 1; i < tree_num_; i++)
    {   
        tree_[i].value = "xx"; 
        reader->GetShort(&num);
        reader->GetChar(&type);
        if (type == 0)
            tree_[num].l = &tree_[i]; 
        else
            tree_[num].r = &tree_[i];
    } 

    reader->GetShort(&sym_num);
    for(unsigned short i = 0; i < sym_num; i++)
    {     
        reader->GetShort(&num); 
        reader->GetChar(&sym);        
        tree_[num].value = "x";
        tree_[num].value[0] = sym;
    }
}
