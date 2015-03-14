#ifndef _INTERFACE_ARCHIVER_H_
#define _INTERFACE_ARCHIVER_H_

#include <cstdio>

class Archiver {
public:
	virtual void compress(const char *inputFileName, const char *outputFileName) = 0;
	virtual void decompress(const char *inputFileName, const char *outputFileName) = 0;
};

#endif // _INTERFACE_ARCHIVER_H_