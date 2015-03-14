#ifndef _LZ77_LZ77ARCHIVER_H_
#define _LZ77_LZ77ARCHIVER_H_

#include "../interface/Archiver.h"

class LZ77Archiver : public Archiver {
public:
	LZ77Archiver();
	void compress(const char *inputFileName, const char *outputFileName);
	void decompress(const char *inputFileName, const char *outputFileName);
	~LZ77Archiver();
};

#endif // _LZ77_LZ77ARCHIVER_H_