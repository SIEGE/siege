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

/**
 * Title: Windowing
 */

#ifndef __SIEGE_CORE_WINDOW_H__
#define __SIEGE_CORE_WINDOW_H__

#include "../graphics/image.h"
#include "../modules/window.h"

#include <stdarg.h>

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

#ifdef SG_BUILD_LIBRARY
char* _sg_winTitle;
void* _sg_winHandle;
void* _sg_gfxHandle;
SGCoreWindowCallbacks _sg_winCallbacks;
#endif // SG_BUILD_LIBRARY

void SG_EXPORT _sg_cbWindowOpen(void* window);
void SG_EXPORT _sg_cbWindowClose(void* window);
void SG_EXPORT _sg_cbWindowResize(void* window, SGuint width, SGuint height);

SGbool SG_EXPORT _sgWindowInit(void);
SGbool SG_EXPORT _sgWindowDeinit(void);

/**
 * \defgroup Window
 * \ingroup Core
 */

/**
 * \ingroup Window
 * \brief Open a window
 * \param width Window width
 * \param height Window height
 * \param bpp Window bits per pixel
 * \param flags Window open flags
 * \return SG_TRUE if successful, SG_FALSE otherwise
 * \note
 *	If a window was already opened, it closes the "old" window and reopens a new one
 */
SGbool SG_EXPORT sgWindowOpen(SGuint width, SGuint height, SGuint bpp, SGenum flags);
/**
 * \ingroup Window
 * \brief Is the window opened?
 * \return SG_TRUE if it is, SG_FALSE otherwise
 */
SGbool SG_EXPORT sgWindowIsOpened(void);
/**
 * \ingroup Window
 * \brief Close the window
 */
void SG_EXPORT sgWindowClose(void);

void SG_EXPORT sgWindowSetIcon(SGImageData* idata);

/**
 * \name Title
 */
/// @{
/**
 * \ingroup Window
 * \brief Set the window title with printf-like formatting
 */
void SG_EXPORT sgWindowSetTitlef(const char* format, ...);
/**
 * \ingroup Window
 * \brief Set the window title with vprintf-like formatting
 * \param format The format, equivalent to format in vprintf
 * \param args The va_list of arguments, equivalent to the arguments in vprintf
 */
void SG_EXPORT sgWindowSetTitlefv(const char* format, va_list args);
/**
 * \ingroup Window
 * \brief Set the window title
 * \param[in] title The new title
 *
 * This function takes a normal string and sets it as the title. It is called by the \ref sgWindowSetTitlef "f" and \ref sgWindowSetTitlefv "fv" functions.
 */
void SG_EXPORT sgWindowSetTitle(const char* title);
/**
 * \ingroup Window
 * \brief Get the window title
 * \return The window title - this value should \b not be freed!
 */
char* SG_EXPORT sgWindowGetTitle(void);
/// @}

/**
 * \name Size
 */
/// @{
/**
 * \ingroup Window
 * \brief Resize the window
 * \param[in] width New window width
 * \param[in] height New window height
 *
 * \sa
 *	sgWindowGetSize
 *	sgWindowSetWidth
 *	sgWindowSetHeight
 */
void SG_EXPORT sgWindowSetSize(SGuint width, SGuint height);
/**
 * \ingroup Window
 * \brief Get the window size
 * \param[out] width Pointer to the window width
 * \param[out] height Pointer to the window height
 *
 * \sa
 *	sgWindowSetSize
 *	sgWindowGetWidth
 *	sgWindowGetHeight
 */
void SG_EXPORT sgWindowGetSize(SGuint* width, SGuint* height);

/**
 * \ingroup Window
 * \brief Change the width of the window
 * \param[in] width New window width
 *
 * This function preserves the window height, setting its width only.
 *
 * \note
 *	If both width and height are required to be set, consider \ref sgWindowSetSize "sgWindowSetSize".
 *
 * \sa
 *	sgWindowGetWidth
 *	sgWindowSetSize
 *	sgWindowSetHeight
 */
void SG_EXPORT sgWindowSetWidth(SGuint width);
/**
 * \ingroup Window
 * \brief Get the width of the window
 * \return The window width or 0 if not opened
 *
 * \note
 *	If both width and height are required, consider \ref sgWindowGetSize "sgWindowGetSize".
 *
 * \sa
 *	sgWindowSetWidth
 *	sgWindowGetSize
 *	sgWindowGetHeight
 */
SGuint SG_EXPORT sgWindowGetWidth(void);
/**
 * \ingroup Window
 * \brief Change the height of the window
 * \param[in] height New window height
 *
 * This function preserves the window width, setting its height only.
 *
 * \note
 *	If both width and height are required to be set, consider \ref sgWindowSetSize "sgWindowSetSize".
 *
 * \sa
 *	sgWindowGetHeight
 *	sgWindowSetSize
 *	sgWindowSetWidth
 */
void SG_EXPORT sgWindowSetHeight(SGuint height);
/**
 * \ingroup Window
 * \brief Get the height of the window
 * \return The window height or 0 if not opened
 *
 * \note
 *	If both width and height are required, consider \ref sgWindowGetSize "sgWindowGetSize".
 *
 * \sa
 *	sgWindowSetHeight
 *	sgWindowGetSize
 *	sgWindowGetWidth
 */
SGuint SG_EXPORT sgWindowGetHeight(void);
/// @}

SGfloat SG_EXPORT sgWindowGetFPSLimit(void);
void SG_EXPORT sgWindowSetFPSLimit(SGfloat limit);
SGfloat SG_EXPORT sgWindowGetFPS(void);

/// @{
/**
 * \ingroup Window
 * \brief Swap the window front and back buffers
 */
void SG_EXPORT sgWindowSwapBuffers(void);
/// @}
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_CORE_WINDOW_H__
