compileFlags := -O2 -Wall -std=c++0x
compileObjFlags := $(compileFlags) -c

build/main: build/main.o build/LZ77Archiver.o
	g++ $(compileFlags) build/main.o build/LZ77Archiver.o -o build/main
build/main.o: src/interface/Archiver.h src/LZ77/LZ77Archiver.h src/main.cpp
	g++ $(compileObjFlags) src/main.cpp -o build/main.o
build/LZ77Archiver.o: src/interface/Archiver.h src/LZ77/LZ77Archiver.h src/LZ77/LZ77Archiver.cpp
	g++ $(compileObjFlags) src/LZ77/LZ77Archiver.cpp -o build/LZ77Archiver.o

clean: 
	rm -rf build/*.o