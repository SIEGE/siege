#ifndef __SIEGE_UTIL_RCOUNT_H__
#define __SIEGE_UTIL_RCOUNT_H__

#include "../common.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct SGRCount
{
    void* handle;
    SGbool wasz;
} SGRCount;

SG_EXPORT SGRCount* SG_CALL sgRCountInit(SGRCount* cnt);
SG_EXPORT void SG_CALL sgRCountDeinit(SGRCount* cnt);

SG_EXPORT void SG_CALL sgRCountInc(SGRCount* cnt);
SG_EXPORT SGbool SG_CALL sgRCountDec(SGRCount* cnt);

SG_EXPORT SGbool SG_CALL sgRCountCheck(SGRCount* cnt);

SG_EXPORT SGuint SG_CALL sgRCountGetValDBG(SGRCount* cnt);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif /* __SIEGE_UTIL_RCOUNT_H__ */
