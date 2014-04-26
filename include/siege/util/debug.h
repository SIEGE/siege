#ifndef __SIEGE_UTIL_DEBUG_H__
#define __SIEGE_UTIL_DEBUG_H__

#include "../common.h"

#define SG_DEBUG_FILE __FILE__
#define SG_DEBUG_LINE __LINE__
#ifdef _MSC_VER
#define SG_DEBUG_FUNCTION __FUNCTION__
#else
#define SG_DEBUG_FUNCTION __func__
#endif

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/* TODO: stacktrace API */

#ifdef __cplusplus
}
#endif // __cplusplus

#endif /* __SIEGE_UTIL_DEBUG_H__ */
