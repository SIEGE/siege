/*
    Copyright (c) 2007 SIEGE Development Team
    All rights reserved.

    This file is part of libSIEGE.

    This software is copyrighted work licensed under the terms of the
    2-clause BSD license. Please consult the file "license.txt" for
    details.

    If you did not recieve the file with this program, please email
    Tim Chas <darkuranium@gmail.com>.
*/

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

SGRand* SG_EXPORT sgRandCreate32(SGenum type, SGuint seed, SGuint index);
void SG_EXPORT sgRandDestroy(SGRand* rand);
void SG_EXPORT sgRandSeed32(SGRand* rand, SGuint seed, SGuint index);
SGuint SG_EXPORT sgRandGen32(SGRand* rand);

// aliases
void SG_EXPORT sgRandDestroy32(SGRand* rand);

#endif // __SIEGE_UTIL_RAND_H__
