#ifndef _LZ77ARCHIVER_H_
#define _LZ77ARCHIVER_H_

#include "Archiver.h"

class LZ77Archiver : public Archiver {
public:
	LZ77Archiver();
	void read(FILE *file);
	void run();
	void write(FILE *file);
};

#endif // _LZ77ARCHIVER_H_