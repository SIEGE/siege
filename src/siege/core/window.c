/*
 * Copyright (c) 2007 SIEGE Development Team
 * All rights reserved.
 *
 * This file is part of libSIEGE.
 *
 * This software is copyrighted work licensed under the terms of the
 * 2-clause BSD license. Please consult the file "license.txt" for
 * details.
 *
 * If you did not recieve the file with this program, please email
 * Tim Chas <darkuranium@gmail.com>.
 */

#define SG_BUILD_LIBRARY
#include <siege/core/core.h>
#include <siege/core/entity.h>
#include <siege/core/window.h>
#include <siege/graphics/viewport.h>
#include <siege/input/joystick.h>
#include <siege/input/keyboard.h>
#include <siege/input/mouse.h>
#include <siege/modules/graphics.h>
#include <siege/modules/window.h>
#include <siege/util/string.h>
#include <siege/util/time.h>

#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

void SG_EXPORT _sg_cbWindowOpen(void* window)
{
	sgEventCall(SG_EV_INTERNAL, (SGuint)1, (SGenum)SG_EVF_WINOPEN);
}
void SG_EXPORT _sg_cbWindowClose(void* window)
{
	sgEventCall(SG_EV_INTERNAL, (SGuint)1, (SGenum)SG_EVF_WINCLOSE);
	sgStop(0);
}
void SG_EXPORT _sg_cbWindowResize(void* window, SGuint width, SGuint height)
{
	sgEventCall(SG_EV_INTERNAL, (SGuint)1, (SGenum)SG_EVF_WINRESIZE, width, height);
}

SGbool SG_EXPORT _sgWindowInit(void)
{
	_sg_winTitle = NULL;
	_sg_winCallbacks.open = NULL;//_sg_cbWindowOpen;
	_sg_winCallbacks.close = _sg_cbWindowClose;
	_sg_winCallbacks.resize = NULL;//_sg_cbWindowResize;

	if(psgmCoreWindowCreate != NULL)
		psgmCoreWindowCreate(&_sg_winHandle);

	if(psgmCoreWindowSetCallbacks != NULL)
		psgmCoreWindowSetCallbacks(_sg_winHandle, &_sg_winCallbacks);

	return SG_TRUE;
}

SGbool SG_EXPORT _sgWindowDeinit(void)
{
	if(psgmCoreWindowDestroy != NULL)
		psgmCoreWindowDestroy(_sg_winHandle);
	free(_sg_winTitle);
	return SG_TRUE;
}

SGbool SG_EXPORT sgWindowOpen(SGuint width, SGuint height, SGuint bpp, SGenum flags)
{
	if(width == 0)
		width = 640;
	if(height == 0)
		height = 480;
	if(bpp == 0)
		bpp = 32;

	if(sgWindowIsOpened())
		sgWindowClose();

	if(psgmCoreWindowOpen != NULL)
		psgmCoreWindowOpen(_sg_winHandle, width, height, bpp, flags);

	sgWindowSetTitle("SIEGE Window");

	sgWindowGetSize(&width, &height);
	if(psgmGraphicsContextCreate != NULL)
		psgmGraphicsContextCreate(&_sg_gfxHandle, width, height, bpp);

	_sg_viewMain = sgViewportCreate4i(0, 0, width, height);

	_sg_cbWindowOpen(_sg_winHandle);
	_sg_cbWindowResize(_sg_winHandle, width, height);
	return SG_TRUE;
}
SGbool SG_EXPORT sgWindowIsOpened(void)
{
	SGbool opened = SG_FALSE;
	if(psgmCoreWindowIsOpened != NULL)
		psgmCoreWindowIsOpened(_sg_winHandle, &opened);
	return opened;
}
void SG_EXPORT sgWindowClose(void)
{
	if(psgmGraphicsContextDestroy != NULL)
		psgmGraphicsContextDestroy(_sg_gfxHandle);
	if(psgmCoreWindowClose != NULL)
		psgmCoreWindowClose(_sg_winHandle);
}
void SG_EXPORT sgWindowSetTitlef(const char* format, ...)
{
	va_list args;
	va_start(args, format);
	sgWindowSetTitlefv(format, args);
	va_end(args);
}
void SG_EXPORT sgWindowSetTitlefv(const char* format, va_list args)
{
	char* title = sgPrintfv(format, args);
	sgWindowSetTitle(title);
	free(title);
}
void SG_EXPORT sgWindowSetTitle(const char* title)
{
	int len = strlen(title) + 1;
	_sg_winTitle = realloc(_sg_winTitle, len);
	strcpy(_sg_winTitle, title);
	if(psgmCoreWindowSetTitle != NULL)
		psgmCoreWindowSetTitle(_sg_winHandle, _sg_winTitle);
}
char* SG_EXPORT sgWindowGetTitle(void)
{
	return _sg_winTitle;
}
void SG_EXPORT sgWindowSetSize(SGuint width, SGuint height)
{
	if(psgmCoreWindowSetSize != NULL)
		psgmCoreWindowSetSize(_sg_winHandle, width, height);
	if(psgmGraphicsContextResize != NULL)
		psgmGraphicsContextResize(_sg_gfxHandle, width, height);
}
void SG_EXPORT sgWindowGetSize(SGuint* width, SGuint* height)
{
	SGuint w, h;
	if(psgmCoreWindowGetSize != NULL)
		psgmCoreWindowGetSize(_sg_winHandle, &w, &h);
	if(width != NULL)
		*width = w;
	if(height != NULL)
		*height = h;
}
void SG_EXPORT sgWindowSetWidth(SGuint width)
{
	SGuint height;
	sgWindowGetSize(NULL, &height);
	sgWindowSetSize(width, height);
}
SGuint SG_EXPORT sgWindowGetWidth(void)
{
	SGuint width;
	sgWindowGetSize(&width, NULL);
	return width;
}
void SG_EXPORT sgWindowSetHeight(SGuint height)
{
	SGuint width;
	sgWindowGetSize(&width, NULL);
	sgWindowSetSize(width, height);
}
SGuint SG_EXPORT sgWindowGetHeight(void)
{
	SGuint height;
	sgWindowGetSize(NULL, &height);
	return height;
}
void SG_EXPORT sgWindowSwapBuffers(void)
{
    if(psgmCoreWindowSwapBuffers != NULL)
        psgmCoreWindowSwapBuffers(_sg_winHandle);
	_sgMouseUpdate();
	_sgKeyboardUpdate();
}
SGfloat SG_EXPORT sgGetFPSLimit(void)
{
    return _sg_FPS;
}
void SG_EXPORT sgSetFPSLimit(SGfloat limit)
{
    _sg_FPSOrigin = sgGetTime();
    _sg_FPS = limit;
    _sg_FPSInNanoseconds = _sg_FPS * 1000000000;
}
