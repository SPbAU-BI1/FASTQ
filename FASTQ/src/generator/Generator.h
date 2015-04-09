#ifndef _GENERATOR_H_
#define _GENERATOR_H_

#include <stdio.h>

class Generator {
public:
    void run(const char *filename, int length);
private:
    const char *alphabet = "ACGT";
};

#endif //_GENERATOR_H_