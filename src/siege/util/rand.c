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

#define SG_BUILD_LIBRARY
#include <siege/util/rand.h>

#include <stdlib.h>

void SG_EXPORT _sgRandMersenne32Create(SGRand* rand)
{
    rand->data = malloc(sizeof(SGuint) * 625);
}
void SG_EXPORT _sgRandMersenne32Destroy(SGRand* rand)
{
    free(rand->data);
}
void SG_EXPORT _sgRandMersenne32Seed(SGRand* rand, SGulong seed, SGulong index)
{
    SGuint* ind = &((SGuint*)rand->data)[0];
    SGuint* mt = &((SGuint*)rand->data)[1];

    mt[0] = seed;
    *ind = index % 624;
    SGuint i;
    for(i = 1; i < 624; i++)
        mt[i] = (0x6C078965 * (mt[i-1] ^ (mt[i-1] >> 30))) & 0xFFFFFFFF;
}
void SG_EXPORT _sgRandMersenne32GenNumbers(SGRand* rand)
{
    //SGuint* ind = &((SGuint*)rand->data)[0];
    SGuint* mt = &((SGuint*)rand->data)[1];

    SGuint i;
    for(i = 0; i < 624; i++)
    {
        SGuint y = (mt[i] >> 31) + (mt[(i+1)%624] & 0x7FFFFFFF);
        mt[i] = mt[(i + 397)%624] ^ (y >> 1);
        if((y % 2) == 1)
            mt[i] = mt[i] ^ 0x9908B0DF;
    }
}
SGulong SG_EXPORT _sgRandMersenne32Gen(SGRand* rand)
{
    SGuint* ind = &((SGuint*)rand->data)[0];
    SGuint* mt = &((SGuint*)rand->data)[1];

    if(*ind == 0)
        _sgRandMersenne32GenNumbers(rand);

    SGuint y = mt[*ind];
    y = y ^ (y >> 11);
    y = y ^ ((y << 7) & 0x9D2C5680);
    y = y ^ ((y << 15) & 0xEFC60000);
    y = y ^ (y >> 18);

    *ind = (*ind + 1) % 624;
    return y;
}

SGRand* SG_EXPORT sgRandCreate(SGenum type)
{
    static SGRandCallbacks cbsMersenne32 = {
        _sgRandMersenne32Create, _sgRandMersenne32Destroy,
        _sgRandMersenne32Seed, _sgRandMersenne32Gen
        };

    SGRandCallbacks cbs = { NULL };
    switch(type)
    {
        case SG_RAND_MT19937: cbs = cbsMersenne32; break;
    }

    SGRand* rand = sgRandCreateCB(&cbs);
    if(!rand)
        return NULL;

    rand->type = type;

    return rand;
}
SGRand* SG_EXPORT sgRandCreateCB(SGRandCallbacks* cbs)
{
    SGRand* rand = malloc(sizeof(SGRand));
    if(rand == NULL)
        return NULL;

    rand->type = SG_RAND_USER;
    rand->stime = time(NULL);

    rand->cbs = *cbs;

    return rand;
}
void SG_EXPORT sgRandDestroy(SGRand* rand)
{
    if(rand == NULL)
        return;

    if(rand->cbs.destroy)
        rand->cbs.destroy(rand);
    free(rand);
}

void SG_EXPORT sgRandSeed(SGRand* rand, SGulong seed, SGulong index)
{
    if(rand == NULL)
        return;

    if(!seed)
        seed = rand->stime;

    if(rand->cbs.seed)
        rand->cbs.seed(rand, seed, index);
}

SGulong SG_EXPORT sgRandGen(SGRand* rand)
{
    if(rand == NULL)
        return 0;

    if(rand->cbs.gen)
        return rand->cbs.gen(rand);
    return 0;
}

