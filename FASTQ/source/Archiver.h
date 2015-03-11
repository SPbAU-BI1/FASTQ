#ifndef _ARCHIVER_H_
#define _ARCHIVER_H_

#include <cstdio>

class Archiver {
public:
	Archiver();
	virtual void read(FILE *file) = 0;
	virtual void run() = 0;
	virtual void write(FILE *file) = 0;
};

#endif // _ARCHIVER_H_