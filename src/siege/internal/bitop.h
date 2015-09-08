#ifndef __SIEGE_INTERNAL_BITOP_H__
#define __SIEGE_INTERNAL_BITOP_H__

#include <siege/common.h>
#include <limits.h>

#define ARR_BITS        (sizeof(SGulong) * CHAR_BIT)
#define ARR_MASK        (ARR_BITS - 1)

#define ARR_BITITEM(arr, n) ((arr)[(n) / ARR_BITS])
#define ARR_BITLENGTH(n)    (((n) + (ARR_BITS - 1)) / ARR_BITS)

#define SET_BIT(arr, n, val)    (arr = (val) ? ((arr) | (((SGulong)1) << (n))) : ((arr) & ~(((SGulong)1) << (n))))
#define GET_BIT(arr, n)         ((arr >> (n)) & 1)

#define SET_BIT_PREV(base, n, val)  SET_BIT(_sg_##base##Prev, n, val)
#define GET_BIT_PREV(base, n)       GET_BIT(_sg_##base##Prev, n)

#define SET_BIT_CURR(base, n, val)  SET_BIT(_sg_##base##Curr, n, val)
#define GET_BIT_CURR(base, n)       GET_BIT(_sg_##base##Curr, n)

#define SET_BITARR(arr, n, val) SET_BIT(ARR_BITITEM(arr, n), (n) & ARR_MASK, val)
#define GET_BITARR(arr, n)      GET_BIT(ARR_BITITEM(arr, n), (n) & ARR_MASK)

#define SET_BITARR_PREV(base, n, val)  SET_BITARR(_sg_##base##Prev, n, val)
#define GET_BITARR_PREV(base, n)       GET_BITARR(_sg_##base##Prev, n)

#define SET_BITARR_CURR(base, n, val)  SET_BITARR(_sg_##base##Curr, n, val)
#define GET_BITARR_CURR(base, n)       GET_BITARR(_sg_##base##Curr, n)

#endif /* __SIEGE_INTERNAL_BITOP_H__ */
