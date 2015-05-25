srcdir = src
bindir = bin
objdir = obj
exec = main

#test_srcdir = test

VPATH = $(srcdir) $(srcdir)/Archiver/Huffman $(srcdir)/Archiver/LZ77 $(srcdir)/Archiver/LZW $(srcdir)/Archiver/FASTQ $(srcdir)/InputOutput/Buffered $(srcdir)/InputOutput/StreamReader $(srcdir)/InputOutput/ArrayReaderWriter $(srcdir)/InputOutput/Bit $(srcdir)/Generator $(bindir) $(objdir)
CXX = g++
CXXFLAGS = -O2 -Wall -pedantic -Wextra -std=c++11

sources = main.cpp HuffmanArchiver.cpp LZ77Archiver.cpp LZWArchiver.cpp Trie.cpp TrieNode.cpp FASTQArchiver.cpp BufferedReader.cpp BufferedWriter.cpp StreamReader.cpp ArrayReaderWriter.cpp Generator.cpp BitReader.cpp BitWriter.cpp
objects = $(sources:.cpp=.o)

all: $(bindir) $(objdir) $(exec)

$(bindir):
	mkdir -p $(bindir)

$(objdir):
	mkdir -p $(objdir)

$(exec): $(objects)
	$(CXX) $(CXXFLAGS) $(addprefix $(objdir)/, $(objects)) -o $(bindir)/$@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $(objdir)/$@

run: all
	$(bindir)/$(exec)

#test_sources = Test.cpp Test_shared_ptr.cpp test.cpp Complex.cpp Shared_ptr.cpp
#test_objects = $(test_sources:.cpp=.o)
#test_exec = shared_test

#test: $(bindir) $(objdir) $(test_exec)
#   valgrind --leak-check=full $(bindir)/$(test_exec)

#$(test_exec): $(test_objects)
#   $(CXX) $(CXXFLAGS) $(addprefix $(objdir)/, $(test_objects)) -o $(bindir)/$@

clean:
	rm -rf bin/
	rm -rf obj/
	rm -rf *.o
