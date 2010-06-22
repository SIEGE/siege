#ifndef __SIEGE_H__
#define __SIEGE_H__

#ifndef SG_LEGACY_API
// WARNING: this will be removed once SIEGE is merged in
#define SG_LEGACY_API
#endif // SG_LEGACY_API

#ifdef SG_LEGACY_API
#include "backend.h"
#else
// normal siege.h code goes in here
#endif // SG_LEGACY_API

#include "common.h"

#endif // __SIEGE_H__
