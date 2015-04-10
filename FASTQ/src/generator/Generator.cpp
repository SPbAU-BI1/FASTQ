#include "Generator.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void Generator::run(const char *filename, int length) {
    FILE *f_out = fopen(filename, "w");
    srand(time(NULL));
    
    for (int i = 0; i < length; i++)
        fprintf(f_out, "%c", alphabet[rand() % 4]);   
	fclose(f_out);
}
