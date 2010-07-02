#ifndef __LOAD_H__
#define __LOAD_H__

typedef struct LFile
{
    SF_INFO info;
    SNDFILE* snd;

    SGuint format;
    SGuint size;
} LFile;

#endif // __LOAD_H__
