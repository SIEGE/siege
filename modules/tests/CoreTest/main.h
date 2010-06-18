#ifndef __MAIN_H__
#define __MAIN_H__

#include <GL/gl.h>
#include "core.h"

void cbOpen(void* window);
void cbClose(void* window);
void cbResize(void* window, SGuint width, SGuint height);
void quit(void);
void draw(SGuint width, SGuint height);
int done;

#endif // __MAIN_H__
