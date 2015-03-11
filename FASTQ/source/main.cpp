#include "LZ77Archiver.h"

int main() {
	Archiver *archiver = new LZ77Archiver();
	archiver->run();
}