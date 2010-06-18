#ifndef __COMMON_H__
#define __COMMON_H__

#define SWM_FALSE 0
#define SWM_TRUE  1

#define SWM_COPY       (1<<0)
#define SWM_CONV       (1<<1)
#define SWM_AUTOREMOVE (1<<2)

#define SWM_INT8   (1<<0)
#define SWM_INT16  (1<<1)
//#define SWM_INT24  (1<<2)
#define SWM_INT32  (1<<3)

#define SWM_FLOAT  (1<<8)
#define SWM_DOUBLE (1<<9)

#define SWM_SIGNED   (1<<16)
#define SWM_UNSIGNED (1<<17)

#define SWM_LE (1<<18)
#define SWM_BE (1<<19)

#endif // __COMMON_H__
