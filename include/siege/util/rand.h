/*
    Copyright (c) 2007 SIEGE Development Team
    All rights reserved.

    This file is part of libSIEGE.

    This software is copyrighted work licensed under the terms of the
    2-clause BSD license. Please consult the file "COPYING.txt" for
    details.

    If you did not recieve the file with this program, please email
    Tim Chas <darkuranium@gmail.com>.
*/

#ifndef __SIEGE_UTIL_RAND_H__
#define __SIEGE_UTIL_RAND_H__

#include "../common.h"

#include <time.h>

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

#define SG_RAND_USER    0
#define SG_RAND_MT19937 1
#define SG_RAND_MERSENNE32 SG_RAND_MT19937
#define SG_RAND_POSIX48 2

struct SGRand;

typedef void SG_CALL (SGRandCreateFunction)(struct SGRand* rand);
typedef void SG_CALL (SGRandDestroyFunction)(struct SGRand* rand);
typedef void SG_CALL (SGRandSeedFunction)(struct SGRand* rand, SGulong seed);
typedef SGulong SG_CALL (SGRandGenFunction)(struct SGRand* rand);

typedef struct SGRandCallbacks
{
    SGRandCreateFunction* create;
    SGRandDestroyFunction* destroy;
    SGRandSeedFunction* seed;
    SGRandGenFunction* gen;
} SGRandCallbacks;

typedef struct SGRand
{
    SGenum type;
    time_t stime;
    void* data;
    SGRandCallbacks cbs;
    SGulong max;
} SGRand;

SGRand* SG_CALL sgRandInit(SGRand* rand, SGenum type);
SGRand* SG_CALL sgRandInitCB(SGRand* rand, const SGRandCallbacks* cbs, SGulong max);
void SG_CALL sgRandDeinit(SGRand* rand);

SGRand* SG_CALL sgRandCreate(SGenum type);
SGRand* SG_CALL sgRandCreateCB(const SGRandCallbacks* cbs, SGulong max);
void SG_CALL sgRandDestroy(SGRand* rand);

void SG_CALL sgRandSeed(SGRand* rand, SGulong seed);

SGulong SG_CALL sgRandGen(SGRand* rand);
float SG_CALL sgRandGenf(SGRand* rand);
float SG_CALL sgRandGen1f(SGRand* rand, float max);
float SG_CALL sgRandGen2f(SGRand* rand, float min, float max);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_UTIL_RAND_H__
