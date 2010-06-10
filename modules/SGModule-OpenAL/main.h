#ifndef __MAIN_H__
#define __MAIN_H__

#include <siege/siege.h>

#ifdef __WIN32
#include <al.h>
#include <alc.h>
#else
#include <AL/al.h>
#include <AL/alc.h>
#endif // __WIN32

ALCdevice* device;
ALCcontext* context;

#endif // __MAIN_H__
