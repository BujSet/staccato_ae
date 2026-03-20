
#include <stdlib.h>
#include <stdio.h>
#include "MersenneTwister.h"

#define ITERS 100000000000      // number of rand vals to produce

int main (int argc, char *argv[]) {
    if (argc != 2) {
       printf("Usage ./%s <SEED>\n", argv[0]);
      exit(1);
    }
    char *eptr;
    MTRand *mt = new MTRand(strtoul(argv[1], &eptr, 10));
    unsigned rnd;
    FILE *bstdout = freopen(NULL, "wb", stdout);
    for (size_t i = 0; i < ITERS; i++) {
        rnd = mt->randInt();
        fwrite(&rnd, sizeof(rnd), 1, bstdout);
    }
    delete mt;    
    FILE *restore_stdout = freopen(NULL, "w", stdout);
    return 0;
}
