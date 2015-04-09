#include <stdlib.h>
#include <stdio.h>
#include <time.h>

const char *s = "ACGT";

const int N = 9000;

int main()
{
    srand(time(NULL));
    FILE *f_out = fopen("../../test_io/test_in.txt", "w");
	for (int i = 0; i < N; i++)
		fprintf(f_out, "%c", s[rand() % 1]);
	fprintf(f_out, "\n");
}