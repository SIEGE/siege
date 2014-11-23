#ifndef __SIEGE_INTERNAL_BITOP_H__
#define __SIEGE_INTERNAL_BITOP_H__

#define SET_BIT(arr, n, val)    (arr = (((SGulong)(val)) << (n)))
#define GET_BIT(arr, n)         ((arr >> (n)) & 1)

#define SET_BIT_PREV(base, n, val)  SET_BIT(_sg_##base##Prev, n, val)
#define GET_BIT_PREV(base, n)       GET_BIT(_sg_##base##Prev, n)

#define SET_BIT_CURR(base, n, val)  SET_BIT(_sg_##base##Curr, n, val)
#define GET_BIT_CURR(base, n)       GET_BIT(_sg_##base##Curr, n)

#endif /* __SIEGE_INTERNAL_BITOP_H__ */
