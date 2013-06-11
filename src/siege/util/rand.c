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

#define SG_BUILD_LIBRARY
#include <siege/util/rand.h>

#include <stdlib.h>

void SG_CALL _sgRandMersenne32Create(SGRand* rand)
{
    rand->data = malloc(sizeof(SGuint) * 625);
}
void SG_CALL _sgRandMersenne32Destroy(SGRand* rand)
{
    free(rand->data);
}
void SG_CALL _sgRandMersenne32Seed(SGRand* rand, SGulong seed, SGulong index)
{
    SGuint* ind = &((SGuint*)rand->data)[0];
    SGuint* mt = &((SGuint*)rand->data)[1];

    mt[0] = seed;
    *ind = index % 624;
    SGuint i;
    for(i = 1; i < 624; i++)
        mt[i] = (0x6C078965 * (mt[i-1] ^ (mt[i-1] >> 30))) & 0xFFFFFFFF;
}
void SG_CALL _sgRandMersenne32GenNumbers(SGRand* rand)
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
SGulong SG_CALL _sgRandMersenne32Gen(SGRand* rand)
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

SGRand* SG_CALL sgRandCreate(SGenum type)
{
    static SGRandCallbacks cbsMersenne32 = {
        _sgRandMersenne32Create, _sgRandMersenne32Destroy,
        _sgRandMersenne32Seed, _sgRandMersenne32Gen
        };

    SGRandCallbacks cbs = { NULL };
    SGulong max = (SGulong)-1;
    switch(type)
    {
        case SG_RAND_MT19937: cbs = cbsMersenne32; max = (SGuint)-1; break;
    }

    SGRand* rand = sgRandCreateCB(&cbs, max);
    if(!rand)
        return NULL;

    rand->type = type;

    return rand;
}
SGRand* SG_CALL sgRandCreateCB(SGRandCallbacks* cbs, SGulong max)
{
    SGRand* rand = malloc(sizeof(SGRand));
    if(rand == NULL)
        return NULL;

    rand->type = SG_RAND_USER;
    rand->stime = time(NULL);

    rand->cbs = *cbs;
    rand->max = max;

    if(rand->cbs.create)
        rand->cbs.create(rand);
    if(rand->cbs.seed)
        rand->cbs.seed(rand, rand->stime, 0);

    return rand;
}
void SG_CALL sgRandDestroy(SGRand* rand)
{
    if(rand == NULL)
        return;

    if(rand->cbs.destroy)
        rand->cbs.destroy(rand);
    free(rand);
}

void SG_CALL sgRandSeed(SGRand* rand, SGulong seed, SGulong index)
{
    if(rand == NULL)
        return;

    if(!seed)
        seed = rand->stime;

    if(rand->cbs.seed)
        rand->cbs.seed(rand, seed, index);
}

SGulong SG_CALL sgRandGen(SGRand* rand)
{
    if(rand == NULL)
        return 0;

    if(rand->cbs.gen)
        return rand->cbs.gen(rand);
    return 0;
}
float SG_CALL sgRandGenf(SGRand* rand)
{
    return sgRandGen(rand) / (float)rand->max;
}
float SG_CALL sgRandGen1f(SGRand* rand, float max)
{
    return sgRandGenf(rand) * max;
}
float SG_CALL sgRandGen2f(SGRand* rand, float min, float max)
{
    return min + sgRandGen1f(rand, max - min);
}
