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

#ifndef __SIEGE_CORE_H__
#define __SIEGE_CORE_H__

#include "../common.h"
#include <stdarg.h>

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

/**
 * \ingroup Core
 * \brief Load a number of modules
 * \param n The number of modules to load
 * \param args The list of modules to load
 * \return The number of successfully loaded modules.
 * \warning
 *	This function should be called \b before \ref sgInit "sgInit"!
 *
 * The "Modules" folder is used to look for the modules.
 * For example, if the module "Foo" is requested, SIEGE will look for it in this order (replace ".so" with whatever the dynamic library ending of the OS is)
 * - Modules/SGModule-Foo.so
 * - Modules/libSGModule-Foo.so
 * - Modules/SGModule-Foo.debug.so
 * - Modules/libSGModule-Foo.debug.so
 * In debug builds, SIEGE tries to find the ".debug." versions first.
 *
 * \sa
 *	sgLoadModules
 *	sgLoadModule
 */
SGuint SG_EXPORT sgLoadModulesv(int n, va_list args);
/**
 * \ingroup Core
 * \brief Load a number of modules
 * \param n The number of modules to load
 * \param ... The list of modules to load
 * \return The number of successfully loaded modules.
 * \warning
 *	This function should be called \b before \ref sgInit "sgInit"!
 *
 * The "Modules" folder is used to look for the modules.
 * For example, if the module "Foo" is requested, SIEGE will look for it in this order (replace ".so" with whatever the dynamic library ending of the OS is)
 * - Modules/SGModule-Foo.so
 * - Modules/libSGModule-Foo.so
 * - Modules/SGModule-Foo.debug.so
 * - Modules/libSGModule-Foo.debug.so
 * In debug builds, SIEGE tries to find the ".debug." versions first.
 *
 * \sa
 *  sgLoadModulesv
 *  sgLoadModule
 */
SGuint SG_EXPORT sgLoadModules(int n, ...);
/**
 * \ingroup Core
 * \brief Load a single module
 * \param name Name of the module to load
 * \return SG_TRUE if successful, SG_FALSE otherwise.
 * \warning
 *	This function should be called \b before \ref sgInit "sgInit"!
 *
 * The "Modules" folder is used to look for the modules.
 * For example, if the module "Foo" is requested, SIEGE will look for it in this order (replace ".so" with whatever the dynamic library ending of the OS is)
 * - Modules/SGModule-Foo.so
 * - Modules/libSGModule-Foo.so
 * - Modules/SGModule-Foo.debug.so
 * - Modules/libSGModule-Foo.debug.so
 * In debug builds, SIEGE tries to find the ".debug." versions first.
 *
 * \sa
 *	sgLoadModules
 */
SGbool SG_EXPORT sgLoadModule(const char* name);
/**
 * \ingroup Core
 * \brief Initialize SIEGE
 * \param width Window width
 * \param height Window height
 * \param bpp Window bits (not bytes!) per pixel
 * \param flags Window open flags
 * \return SG_TRUE on success, SG_FALSE otherwise.
 * \warning
 *	This function should be called \b after \ref sgLoadModule "sgLoadModule" or \ref sgLoadModules "sgLoadModules"!
 *
 * \sa
 *	sgDeinit
 */
SGbool SG_EXPORT sgInit(SGuint width, SGuint height, SGuint bpp, SGenum flags);
/**
 * \ingroup Core
 * \brief Cleanup and deinit SIEGE
 * \return SG_TRUE on success, SG_FALSE otherwise (which would leave the app in a messy state).
 * \warning
 *	This should \b always be the last SIEGE function you call!
 *
 * \sa
 *	sgInit
 */
SGbool SG_EXPORT sgDeinit(void);

/**
 * \ingroup Core
 * \brief Start the SIEGE main loop
 * \return The return code which can be passed to the "return" from main function.
 *
 * \sa
 *	sgLoop
 *	sgStop
 */
SGint SG_EXPORT sgRun(void);
/**
 * \ingroup Core
 * \brief Run a single SIEGE iteration
 * \param[out] code The return code, which can be passed to the "return" from main() function
 * \return SG_TRUE if the program is to continue running, SG_FALSE if an exit has been requested (either via \ref sgStop "sgStop" or the window closed)
 *
 * Example:
 * \code
 *	int main()
 *	{
 *		// ... init here ...
 *		SGint ret;
 *		while(sgLoop(&ret))
 *		{
 *			// drawing goes here
 *
 *			sgWindowSwapBuffers();
 *			sgDrawClear();
 *		}
 *		// ... deinit here ...
 *		return ret;
 *	}
 * \endcode
 *
 * \sa
 *	sgRun
 *	sgStop
 */
SGbool SG_EXPORT sgLoop(SGint* code);
/**
 * \ingroup Core
 * \brief Stop the program main loop
 * \param ret The value to ultimately return from the main() function
 * \warning
 * The loop SIEGE is currently in will currently run to the end before quitting!
 *
 * \sa
 *	sgRun
 *	sgLoop
 */
void SG_EXPORT sgStop(SGint ret);
/**
 * \ingroup Core
 * \brief Get the current tick (number of loops passed)
 * \return The number of loops SIEGE has ran for since the start
 */
SGulong SG_EXPORT sgGetTick(void);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_CORE_H__
