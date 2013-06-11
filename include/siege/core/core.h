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
  * Title: Core
  */

#ifndef __SIEGE_CORE_H__
#define __SIEGE_CORE_H__

#include "../common.h"
#include <stdarg.h>

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

void SG_CALL sgGetVersionv(SGushort* version);
void SG_CALL sgGetVersion(SGushort* vmajor, SGushort* vminor, SGushort* vpatch);
char* SG_CALL sgGetVersionString(void);

char* SG_CALL sgGetCompileDate(void);
char* SG_CALL sgGetCompileTime(void);

/**
 * Functions: sgLoadModule*
 *
 * Load a module or a number of modules.
 *
 * sgLoadModulesv - Load a va_list of modules
 * sgLoadModules  - Load multiple modules
 * sgLoadModule   - Load a single module
 *
 * The "Modules" folder is used to look for the modules.
 *
 * For example, if the module "Foo" is requested, SIEGE will look for it
 * in this order (replace ".so" with whatever the dynamic library ending
 * of the OS is):
 * - Modules/SGModule-Foo.so
 * - Modules/libSGModule-Foo.so
 * - Modules/SGModule-Foo.debug.so
 * - Modules/libSGModule-Foo.debug.so
 *
 * In debug builds, SIEGE tries to find the ".debug." versions first.
 *
 * Warning:
 *     This function should be called *before* sgInit()!
 *
 * Parameters:
 *     n    - The number of modules to load
 *     args - The va_list of modules to load
 *     ...  - List of modules to load (n items)
 *  name - Name of the module to load
 *
 * Returns:
 *     The number of successfully loaded modules.
 */
SGuint SG_CALL sgLoadModulesv(size_t n, va_list args);
SGuint SG_CALL sgLoadModules(size_t n, ...);
SGbool SG_CALL sgLoadModule(const char* name);
/**
 * Function: sgInit
 *
 * Initialize SIEGE.
 *
 * Warning:
 *     This function should be called *after* sgLoadModule() or
 *     sgLoadModules()!
 *
 * Parameters:
 *     flags         - Init flags (can be zero)
 *
 * Returns:
 *     SG_TRUE on success, SG_FALSE otherwise.
 *
 * See Also:
 *    - <sgDeinit>
 */
SGbool SG_CALL sgInit(SGenum flags);
/**
 * Function: sgDeinit
 *
 * Cleanup and deinit SIEGE.
 *
 * Warning: This should *always* be the last SIEGE function you call!
 *
 * Returns:
 *     SG_TRUE on success, SG_FALSE otherwise (which would leave the app
 *     in a messy state).
 *
 * See Also:
 *    - <sgInit>
 */
SGbool SG_CALL sgDeinit(void);
/**
 * Function: sgRun
 *
 * Start the SIEGE main loop.
 *
 * Returns:
 *     A value meant to be returned from the main() function.
 *
 * See Also:
 *     - <sgLoop>
 *  - <sgStop>
 */
SGint SG_CALL sgRun(void);
/**
 * Function: sgLoop
 *
 * Run a single SIEGE iteration.
 *
 * Parameters:
 *     code - The return code, which can be passed to the "return" from
 *         main() function
 *
 * Returns:
 *     - SG_TRUE if the program is to continue running,
 *     - SG_FALSE if an exit has been requested (either via sgStop() or
 *       the window closed).
 *
 * Example:
 * (begin code)
 *
 *    int main()
 *    {
 *        // ... init here ...
 *        SGint ret;
 *        while(sgLoop(&ret))
 *        {
 *            // drawing goes here
 *
 *            sgWindowSwapBuffers();
 *            sgDrawClear();
 *        }
 *        // ... deinit here ...
 *        return ret;
 *    }
 *
 * (end code)
 *
 * See Also:
 *     - <sgRun>
 *  - <sgStop>
 */
SGbool SG_CALL sgLoop(SGint* code);
/**
 * Function: sgStop
 *
 * Stop the program main loop.
 *
 * Warning:
 *     The loop SIEGE is currently in will
 *     (until the implementation is changed otherwise)
 *     run to the end before quitting!
 *
 * Parameters:
 *     ret - The value to ultimately return from the main() function
 *
 * See Also:
 *     - <sgRun>
 *  - <sgLoop>
 */
void SG_CALL sgStop(SGint ret);
/**
 * Function: sgGetTick
 *
 * Get the current tick (number of loops passed).
 *
 * Returns:
 *     The number of loops SIEGE has ran for since the start
 */
SGulong SG_CALL sgGetTick(void);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_CORE_H__
