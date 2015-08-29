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

/**
 * Init flags
 */
#define SG_INIT_RENDERTHREAD 0x04

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
