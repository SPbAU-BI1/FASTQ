#include "LZ77/LZ77Archiver.h"

int main(int argc, char **argv) {
	Archiver *archiver = new LZ77Archiver();
    archiver->compress(argv[1], argv[2]);
}