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
#include <siege/modules/graphics.h>
#include <siege/modules/window.h>
#include <siege/util/string.h>

#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

void SG_EXPORT _sg_cbWindowOpen(void* window)
{
	_SGEntityCall call;
	call = (_SGEntityCall){1, (SGenum[]){SG_EVF_WINOPEN}, (void*[]){NULL}};
	sgEventCall(SG_EV_INTERNAL, &call);
}
void SG_EXPORT _sg_cbWindowClose(void* window)
{
	_SGEntityCall call;
	call = (_SGEntityCall){1, (SGenum[]){SG_EVF_WINCLOSE}, (void*[]){NULL}};
	sgEventCall(SG_EV_INTERNAL, &call);
	sgStop(0);
}
void SG_EXPORT _sg_cbWindowResize(void* window, SGuint width, SGuint height)
{
	_SGEntityCall call;
	call = (_SGEntityCall){1, (SGenum[]){SG_EVF_WINRESIZE}, (void*[]){(SGuint[]){width, height}}};
	sgEventCall(SG_EV_INTERNAL, &call);
}

SGbool SG_EXPORT _sgWindowInit(void)
{
	_sg_winTitle = NULL;
	_sg_winCallbacks.open = NULL;//_sg_cbWindowOpen;
	_sg_winCallbacks.close = _sg_cbWindowClose;
	_sg_winCallbacks.resize = NULL;//_sg_cbWindowResize;

	if(_sg_modWindow.sgmCoreWindowCreate != NULL)
		_sg_modWindow.sgmCoreWindowCreate(&_sg_winHandle);

	if(_sg_modWindow.sgmCoreWindowSetCallbacks != NULL)
		_sg_modWindow.sgmCoreWindowSetCallbacks(_sg_winHandle, &_sg_winCallbacks);

	return SG_TRUE;
}

SGbool SG_EXPORT _sgWindowDeinit(void)
{
	if(_sg_modWindow.sgmCoreWindowDestroy != NULL)
		_sg_modWindow.sgmCoreWindowDestroy(_sg_winHandle);
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

	if(_sg_modWindow.sgmCoreWindowOpen != NULL)
		_sg_modWindow.sgmCoreWindowOpen(_sg_winHandle, width, height, bpp, flags);

	sgWindowSetTitle("SIEGE Window");

	sgWindowGetSize(&width, &height);
	if(_sg_modGraphics.sgmGraphicsContextCreate != NULL)
		_sg_modGraphics.sgmGraphicsContextCreate(&_sg_gfxHandle, width, height, bpp);

	_sg_viewMain = sgViewportCreate4i(0, 0, width, height);

	_sg_cbWindowOpen(_sg_winHandle);
	_sg_cbWindowResize(_sg_winHandle, width, height);
	return SG_TRUE;
}
SGbool SG_EXPORT sgWindowIsOpened(void)
{
	SGbool opened = SG_FALSE;
	if(_sg_modWindow.sgmCoreWindowIsOpened != NULL)
		_sg_modWindow.sgmCoreWindowIsOpened(_sg_winHandle, &opened);
	return opened;
}
void SG_EXPORT sgWindowClose(void)
{
	if(_sg_modGraphics.sgmGraphicsContextDestroy != NULL)
		_sg_modGraphics.sgmGraphicsContextDestroy(_sg_gfxHandle);
	if(_sg_modWindow.sgmCoreWindowClose != NULL)
		_sg_modWindow.sgmCoreWindowClose(_sg_winHandle);
}
void SG_EXPORT sgWindowSetTitleF(char* format, ...)
{
	va_list args;
	va_start(args, format);
	sgWindowSetTitleFV(format, args);
	va_end(args);
}
void SG_EXPORT sgWindowSetTitleFV(char* format, va_list args)
{
	char* title = sgPrintfv(format, args);
	sgWindowSetTitle(title);
	free(title);
}
void SG_EXPORT sgWindowSetTitle(char* title)
{
	int len = strlen(title) + 1;
	_sg_winTitle = realloc(_sg_winTitle, len);
	strcpy(_sg_winTitle, title);
	if(_sg_modWindow.sgmCoreWindowSetTitle != NULL)
		_sg_modWindow.sgmCoreWindowSetTitle(_sg_winHandle, _sg_winTitle);
}
char* SG_EXPORT sgWindowGetTitle(void)
{
	return _sg_winTitle;
}
void SG_EXPORT sgWindowSetSize(SGuint width, SGuint height)
{
	if(_sg_modWindow.sgmCoreWindowSetSize != NULL)
		_sg_modWindow.sgmCoreWindowSetSize(_sg_winHandle, width, height);
	if(_sg_modGraphics.sgmGraphicsContextResize != NULL)
		_sg_modGraphics.sgmGraphicsContextResize(_sg_gfxHandle, width, height);
}
void SG_EXPORT sgWindowGetSize(SGuint* width, SGuint* height)
{
	SGuint w, h;
	if(_sg_modWindow.sgmCoreWindowGetSize != NULL)
		_sg_modWindow.sgmCoreWindowGetSize(_sg_winHandle, &w, &h);
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
	if(_sg_modWindow.sgmCoreWindowSwapBuffers != NULL)
		_sg_modWindow.sgmCoreWindowSwapBuffers(_sg_winHandle);
}
