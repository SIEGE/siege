/*
 * Copyright (c) 2007 SIEGE Development Team
 * All rights reserved.
 *
 * This file is part of libSIEGE.
 *
 * This software is copyrighted work licensed under the terms of the
 * 2-clause BSD license. Please consult the file "COPYING.txt" for
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
void* _sg_gfxHandle;
#endif // SG_BUILD_LIBRARY

void SG_CALL _sg_cbWindowOpen(void);
void SG_CALL _sg_cbWindowClose(void);
void SG_CALL _sg_cbWindowResize(SGuint width, SGuint height);

SGbool SG_CALL _sgWindowInit(void);
SGbool SG_CALL _sgWindowDeinit(void);

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
 *    If a window was already opened, it closes the "old" window and reopens a new one
 */
SGbool SG_CALL sgWindowOpen(SGuint width, SGuint height, SGuint bpp, SGenum flags);
/**
 * \ingroup Window
 * \brief Is the window opened?
 * \return SG_TRUE if it is, SG_FALSE otherwise
 */
SGbool SG_CALL sgWindowIsOpened(void);
/**
 * \ingroup Window
 * \brief Close the window
 */
void SG_CALL sgWindowClose(void);

void SG_CALL sgWindowSetIcon(SGImageData* idata);

/**
 * \name Title
 */
/// @{
/**
 * \ingroup Window
 * \brief Set the window title with printf-like formatting
 */
void SG_CALL sgWindowSetTitlef(const char* format, ...);
/**
 * \ingroup Window
 * \brief Set the window title with vprintf-like formatting
 * \param format The format, equivalent to format in vprintf
 * \param args The va_list of arguments, equivalent to the arguments in vprintf
 */
void SG_CALL sgWindowSetTitlefv(const char* format, va_list args);
/**
 * \ingroup Window
 * \brief Set the window title
 * \param[in] title The new title
 *
 * This function takes a normal string and sets it as the title. It is called by the \ref sgWindowSetTitlef "f" and \ref sgWindowSetTitlefv "fv" functions.
 */
void SG_CALL sgWindowSetTitle(const char* title);
/**
 * \ingroup Window
 * \brief Get the window title
 * \return The window title - this value should \b not be freed!
 */
char* SG_CALL sgWindowGetTitle(void);
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
 *    sgWindowGetSize
 *    sgWindowSetWidth
 *    sgWindowSetHeight
 */
void SG_CALL sgWindowSetSize(SGuint width, SGuint height);
/**
 * \ingroup Window
 * \brief Get the window size
 * \param[out] width Pointer to the window width
 * \param[out] height Pointer to the window height
 *
 * \sa
 *    sgWindowSetSize
 *    sgWindowGetWidth
 *    sgWindowGetHeight
 */
void SG_CALL sgWindowGetSize(SGuint* width, SGuint* height);

/**
 * \ingroup Window
 * \brief Change the width of the window
 * \param[in] width New window width
 *
 * This function preserves the window height, setting its width only.
 *
 * \note
 *    If both width and height are required to be set, consider \ref sgWindowSetSize "sgWindowSetSize".
 *
 * \sa
 *    sgWindowGetWidth
 *    sgWindowSetSize
 *    sgWindowSetHeight
 */
void SG_CALL sgWindowSetWidth(SGuint width);
/**
 * \ingroup Window
 * \brief Get the width of the window
 * \return The window width or 0 if not opened
 *
 * \note
 *    If both width and height are required, consider \ref sgWindowGetSize "sgWindowGetSize".
 *
 * \sa
 *    sgWindowSetWidth
 *    sgWindowGetSize
 *    sgWindowGetHeight
 */
SGuint SG_CALL sgWindowGetWidth(void);
/**
 * \ingroup Window
 * \brief Change the height of the window
 * \param[in] height New window height
 *
 * This function preserves the window width, setting its height only.
 *
 * \note
 *    If both width and height are required to be set, consider \ref sgWindowSetSize "sgWindowSetSize".
 *
 * \sa
 *    sgWindowGetHeight
 *    sgWindowSetSize
 *    sgWindowSetWidth
 */
void SG_CALL sgWindowSetHeight(SGuint height);
/**
 * \ingroup Window
 * \brief Get the height of the window
 * \return The window height or 0 if not opened
 *
 * \note
 *    If both width and height are required, consider \ref sgWindowGetSize "sgWindowGetSize".
 *
 * \sa
 *    sgWindowSetHeight
 *    sgWindowGetSize
 *    sgWindowGetWidth
 */
SGuint SG_CALL sgWindowGetHeight(void);
/// @}

SGfloat SG_CALL sgWindowGetFPSLimit(void);
void SG_CALL sgWindowSetFPSLimit(SGfloat limit);
SGfloat SG_CALL sgWindowGetFPS(void);

/// @{
/**
 * \ingroup Window
 * \brief Swap the window front and back buffers
 */
void SG_CALL sgWindowHandleEvents(void);
void SG_CALL sgWindowSwapBuffers(void);
/// @}
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_CORE_WINDOW_H__
