compileFlags := -O2 -Wall -std=c++0x
compileObjFlags := $(compileFlags) -c

build/main: build/main.o build/LZ77Archiver.o build/Archiver.o
	g++ $(compileFlags) build/main.o build/LZ77Archiver.o build/Archiver.o -o build/main
build/main.o: source/Archiver.h source/LZ77Archiver.h source/main.cpp
	g++ $(compileObjFlags) source/main.cpp -o build/main.o
build/LZ77Archiver.o: source/Archiver.h source/LZ77Archiver.h source/LZ77Archiver.cpp
	g++ $(compileObjFlags) source/LZ77Archiver.cpp -o build/LZ77Archiver.o
build/Archiver.o: source/Archiver.h source/Archiver.cpp
	g++ $(compileObjFlags) source/Archiver.cpp -o build/Archiver.o

clean: 
	rm -rf build/*.o