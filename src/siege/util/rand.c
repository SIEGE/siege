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

/* source: http://pubs.opengroup.org/onlinepubs/007908775/xsh/drand48.html */
typedef struct DataPosix48
{
    SGulong a, c, m, mask;
    SGulong x;
} DataPosix48;
static void SG_CALL _sgPosix48Create(SGRand* rand)
{
    DataPosix48* data = malloc(sizeof(DataPosix48));
    rand->data = data;

    data->a = UINT64_C(0x5DEECE66D);
    data->c = 0xB;
    data->m = UINT64_C(1) << UINT64_C(48);
    data->mask = data->m - 1U;
}
static void SG_CALL _sgPosix48Destroy(SGRand* rand)
{
    free(rand->data);
}
static void SG_CALL _sgPosix48Seed(SGRand* rand, SGulong seed)
{
    DataPosix48* data = rand->data;
    data->x = seed;
}
static SGulong SG_CALL _sgPosix48Gen(SGRand* rand)
{
    DataPosix48* data = rand->data;

    data->x = (data->a * data->x + data->c) & data->mask;
    return data->x;
}

typedef struct DataMersenne
{
    SGuint index;
    SGuint mt[624];
} DataMersenne;
static void SG_CALL _sgRandMersenne32GenNumbers(SGRand* rand)
{
    DataMersenne* mdata = rand->data;

    SGuint i;
    for(i = 0; i < 624; i++)
    {
        SGuint y = (mdata->mt[i] >> 31) + (mdata->mt[(i+1)%624] & 0x7FFFFFFF);
        mdata->mt[i] = mdata->mt[(i + 397)%624] ^ (y >> 1);
        if((y % 2) == 1)
            mdata->mt[i] = mdata->mt[i] ^ 0x9908B0DF;
    }
}
static void SG_CALL _sgRandMersenne32Create(SGRand* rand)
{
    rand->data = malloc(sizeof(DataMersenne));
}
static void SG_CALL _sgRandMersenne32Destroy(SGRand* rand)
{
    free(rand->data);
}
static void SG_CALL _sgRandMersenne32Seed(SGRand* rand, SGulong seed)
{
    DataMersenne* mdata = rand->data;

    mdata->mt[0] = seed;
    mdata->index = 0;
    SGuint i;
    for(i = 1; i < 624; i++)
        mdata->mt[i] = (0x6C078965 * (mdata->mt[i-1] ^ (mdata->mt[i-1] >> 30))) & 0xFFFFFFFF;
}
static SGulong SG_CALL _sgRandMersenne32Gen(SGRand* rand)
{
    DataMersenne* mdata = rand->data;

    if(mdata->index == 0)
        _sgRandMersenne32GenNumbers(rand);

    SGuint y = mdata->mt[mdata->index];
    y = y ^ (y >> 11);
    y = y ^ ((y << 7) & 0x9D2C5680);
    y = y ^ ((y << 15) & 0xEFC60000);
    y = y ^ (y >> 18);

    mdata->index = (mdata->index + 1) % 624;
    return y;
}

SGRand* SG_CALL sgRandInit(SGRand* rand, SGenum type)
{
    static const SGRandCallbacks cbsMersenne32 = {
        _sgRandMersenne32Create, _sgRandMersenne32Destroy,
        _sgRandMersenne32Seed, _sgRandMersenne32Gen
    };
    static const SGRandCallbacks cbsPosix48 = {
        _sgPosix48Create, _sgPosix48Destroy,
        _sgPosix48Seed, _sgPosix48Gen
    };

    if(!rand) return NULL;

    const SGRandCallbacks* cbs = NULL;
    SGulong max = (SGulong)-1;
    switch(type)
    {
        case SG_RAND_MT19937: cbs = &cbsMersenne32; max = (SGuint)-1; break;
        case SG_RAND_POSIX48: cbs = &cbsPosix48; max = (UINT64_C(1) << UINT64_C(48)) - 1U; break;
    }

    if(!sgRandInitCB(rand, cbs, max))
        return NULL;

    rand->type = type;

    return rand;
}
SGRand* SG_CALL sgRandInitCB(SGRand* rand, const SGRandCallbacks* cbs, SGulong max)
{
    if(!rand) return NULL;

    rand->type = SG_RAND_USER;
    rand->stime = time(NULL);

    rand->cbs = *cbs;
    rand->max = max;

    if(rand->cbs.create)
        rand->cbs.create(rand);
    if(rand->cbs.seed)
        rand->cbs.seed(rand, rand->stime);

    return rand;
}
void SG_CALL sgRandDeinit(SGRand* rand)
{
    if(!rand) return;

    if(rand->cbs.destroy)
        rand->cbs.destroy(rand);
}

SGRand* SG_CALL sgRandCreate(SGenum type)
{
    SGRand* rand = malloc(sizeof(SGRand));
    if(!sgRandInit(rand, type))
    {
        free(rand);
        return NULL;
    }
    return rand;
}
SGRand* SG_CALL sgRandCreateCB(const SGRandCallbacks* cbs, SGulong max)
{
    SGRand* rand = malloc(sizeof(SGRand));
    if(!sgRandInitCB(rand, cbs, max))
    {
        free(rand);
        return NULL;
    }
    return rand;
}
void SG_CALL sgRandDestroy(SGRand* rand)
{
    sgRandDeinit(rand);
    free(rand);
}

void SG_CALL sgRandSeed(SGRand* rand, SGulong seed)
{
    if(rand == NULL)
        return;

    if(!seed)
        seed = rand->stime;

    if(rand->cbs.seed)
        rand->cbs.seed(rand, seed);
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
