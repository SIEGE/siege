#ifndef __SIEGE_UTIL_RAND_H__
#define __SIEGE_UTIL_RAND_H__

#include "../common.h"

#define SG_RAND_MT19937 1

#define SG_RAND_MERSENNE SG_RAND_MT19937

typedef struct SGRand
{
    SGenum type;
    SGubyte* data;
} SGRand;

#ifdef SG_BUILD_LIBRARY
SGuint _sg_randSeed;
#endif // SG_BUILD_LIBRARY

SGbool SG_EXPORT _sgRandInit();
SGbool SG_EXPORT _sgRandDeinit();

SGRand* SG_EXPORT sgRandCreate32(SGenum type, SGuint seed, SGuint index);
void SG_EXPORT sgRandDestroy(SGRand* rand);
void SG_EXPORT sgRandSeed32(SGRand* rand, SGuint seed, SGuint index);
SGuint SG_EXPORT sgRandGen32(SGRand* rand);

// aliases
void SG_EXPORT sgRandDestroy32(SGRand* rand);

#endif // __SIEGE_UTIL_RAND_H__
