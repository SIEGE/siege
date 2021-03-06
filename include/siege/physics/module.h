#ifndef __SG_PHYSICS_MODULE_H__
#define __SG_PHYSICS_MODULE_H__

#include "../common.h"
#include "../module.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

SGbool SG_CALL SG_FPTR(_sgPhysicsInit)(void);
SGbool SG_CALL SG_FPTR(_sgPhysicsDeinit)(void);

SGbool SG_CALL _sgPhysicsLoad(void);
SGbool SG_CALL _sgPhysicsUnload(void);

SGbool SG_CALL sgPhysicsIsAvailable(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __SG_PHYSICS_MODULE_H__ */
