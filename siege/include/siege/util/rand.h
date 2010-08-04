#ifndef __SIEGE_UTIL_RAND_H__
#define __SIEGE_UTIL_RAND_H__

#include "../common.h"

#define SG_RAND_MERSENNE 1

typedef struct SGRand
{
    SGenum type;
    SGubyte* data;
} SGRand;

SGbool _sgRandInit();
SGbool _sgRandDeinit();

SGRand* sgRandCreate32(SGenum type, SGuint seed, SGuint index);
void sgRandDestroy(SGRand* rand);
void sgRandSeed32(SGRand* rand, SGuint seed, SGuint index);
SGuint sgRandGen32(SGRand* rand);

// aliases
void sgRandDestroy32(SGRand* rand);

#endif // __SIEGE_UTIL_RAND_H__
