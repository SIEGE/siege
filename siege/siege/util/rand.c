#define SG_BUILD_LIBRARY
#include <siege/util/rand.h>

#include <stdlib.h>

SGbool _sgRandInit()
{
    return SG_TRUE;
}
SGbool _sgRandDeinit()
{
    return SG_TRUE;
}

void _sgRandMersenneCreate32(SGRand* rand)
{
    rand->data = malloc(sizeof(SGuint) * 625);
}
void _sgRandMersenneSeed32(SGRand* rand, SGuint seed, SGuint index)
{
    SGuint* ind = (SGuint*)rand->data;
    SGuint* mt = (SGuint*)rand->data + sizeof(SGuint);

    mt[0] = seed;
    *ind = index % 624;
    SGuint i;
    for(i = 1; i < 624; i++)
        mt[i] = (0x6C078965 * (mt[i-1] ^ (mt[i-1] >> 30))) & 0xFFFFFFFF;
}
void _sgRandMersenneGenNumbers32(SGRand* rand)
{
    //SGuint* ind = (SGuint*)rand->data;
    SGuint* mt = (SGuint*)rand->data + sizeof(SGuint);

    SGuint i;
    for(i = 0; i < 624; i++)
    {
        SGuint y = (mt[i] >> 31) + (mt[(i+1)%624] & 0x7FFFFFFF);
        mt[i] = mt[(i + 397)%624] ^ (y >> 1);
        if((y % 2) == 1)
            mt[i] = mt[i] ^ 0x9908B0DF;
    }
}
SGuint _sgRandMersenneGen32(SGRand* rand)
{
    SGuint* ind = (SGuint*)rand->data;
    SGuint* mt = (SGuint*)rand->data + sizeof(SGuint);

    if(*ind == 0)
        _sgRandMersenneGenNumbers32(rand);

    SGuint y = mt[*ind];
    y = y ^ (y >> 11);
    y = y ^ ((y << 7) & 0x9D2C5680);
    y = y ^ ((y << 15) & 0xEFC60000);
    y = y ^ (y >> 18);

    *ind = (*ind + 1) % 624;
    return y;
}

SGRand* sgRandCreate32(SGenum type, SGuint seed, SGuint index)
{
    SGRand* rand = malloc(sizeof(SGRand));
    if(rand == NULL)
        return NULL;

    rand->type = type;
    switch(type)
    {
        case SG_RAND_MERSENNE:
            _sgRandMersenneCreate32(rand);
            _sgRandMersenneSeed32(rand, seed, index);
            break;

        default:
            free(rand);
            return NULL;
    }

    return rand;
}
void sgRandDestroy(SGRand* rand)
{
    if(rand == NULL)
        return;

    free(rand->data);
    free(rand);
}
void sgRandSeed32(SGRand* rand, SGuint seed, SGuint index)
{
    if(rand == NULL)
        return;

    switch(rand->type)
    {
        case SG_RAND_MERSENNE:
            _sgRandMersenneSeed32(rand, seed, index);
            break;

        default:
            break;
    }
}
SGuint sgRandGen32(SGRand* rand)
{
    if(rand == NULL)
        return 0;

    switch(rand->type)
    {
        case SG_RAND_MERSENNE:
            return _sgRandMersenneGen32(rand);

        default:
            return 0;
    }
    // should never reach...
    return 0;
}

// aliases
void sgRandDestroy32(SGRand* rand)
{
    sgRandDestroy(rand);
}
