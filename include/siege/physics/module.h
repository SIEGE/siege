#ifndef __SG_PHYSICS_MODULE_H__
#define __SG_PHYSICS_MODULE_H__

#include "../common.h"
#include "../module.h"

SGbool SG_CALL SG_FPTR(_sgPhysicsInit)(void);
SGbool SG_CALL SG_FPTR(_sgPhysicsDeinit)(void);

SGbool SG_CALL _sgPhysicsLoad(void);
SGbool SG_CALL _sgPhysicsUnload(void);

SGbool SG_CALL sgPhysicsIsAvailable(void);

#endif /* __SG_PHYSICS_MODULE_H__ */
