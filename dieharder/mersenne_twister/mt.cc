
#include <stdlib.h>
#include <stdio.h>
#include <cstdint>
#include "MersenneTwister.h"

//#define ITERS 100 // 100000000000      // number of rand vals to produce
//#define RESEED_RATE 50.0

#define c1 4294967294U
#define c2 4294967288U
#define c3 4294967280U
#define c4 4294967168U

static unsigned s1;
static unsigned s2;
static unsigned s3;
static unsigned s4;

unsigned taus113(void) {
    s1 = ( ( s1 & c1 ) << 18 ) ^ ( ( ( s1 <<  6 ) ^ s1 ) >> 13 );
    s2 = ( ( s2 & c2 ) <<  2 ) ^ ( ( ( s2 <<  2 ) ^ s2 ) >> 27 );
    s3 = ( ( s3 & c3 ) <<  7 ) ^ ( ( ( s3 << 13 ) ^ s3 ) >> 21 );
    s4 = ( ( s4 & c4 ) << 13 ) ^ ( ( ( s4 <<  3 ) ^ s4 ) >> 12 );
    return (s1 ^ s2 ^ s3 ^ s4 ) & 0xffffffff;
}

double toPercentage(unsigned input) {
    double max = (double) ((unsigned) 0xFFFFFFFF);
    double val = 100.0 * (((double)input) / max);
    return val;
}

int rdseed_step(uint64_t *rand) {
    unsigned char ok;

    __asm__ volatile("rdseed %0;"
                     "setc %1"
                     : "=r"(*rand), "=qm"(ok));

    return (int)ok;
}

int main (int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: ./%s <ITERS> <RESEED_RATE>\n", argv[0]);
        exit(1);
    }
    uint64_t ITERS = 100000;
    char *eptr;
    ITERS = strtoul(argv[1], &eptr, 10);
    double RESEED_RATE = 0.0;
    RESEED_RATE = strtod(argv[2], &eptr);
    if (RESEED_RATE < 0.0) {
        printf("ERROR: Reseed rate must be >= 0.0!\n");
        exit(1);
    }
    if (RESEED_RATE > 100.0) {
        printf("ERROR: Reseed rate must be <= 100.0!\n");
        exit(1);
    }


    unsigned rnd;
    unsigned long new_seed;
    MTRand *mt = new MTRand();
    s1 = 16289;
    s2 = 8;
    s3 = 16;
    s4 = 128;    
    FILE *bstdout = freopen(NULL, "wb", stdout);
    for (size_t i = 0; i < ITERS; i++) {
        if (toPercentage(taus113()) < RESEED_RATE) {
            while(rdseed_step(&new_seed) == 0);
            mt->seed(new_seed);
        }
        rnd = mt->randInt();
        fwrite(&rnd, sizeof(rnd), 1, bstdout);
    }
    delete mt;    
    freopen(NULL, "w", stdout);
    return 0;
}
