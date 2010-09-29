#ifndef __MAIN_H__
#define __MAIN_H__

#include <siege/siege.h>

#include <vlc/vlc.h>

libvlc_instance_t* vlcInstance;
libvlc_exception_t vlcEx;

int exRaised(libvlc_exception_t* ex);

#endif // __MAIN_H__
