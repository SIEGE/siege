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

#ifndef __SIEGE_MODULES_INPUT_H__
#define __SIEGE_MODULES_INPUT_H__
#include "../common.h"
#include "../util/link.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus
	typedef struct SGCoreJoystickCallbacks
	{
		void SG_EXPORT (*button)(void* joystick, SGuint button, SGbool down);
		//void SG_EXPORT (*button)(void* joystick, SGbool* buttons);
		//void SG_EXPORT (*move)(void* joystick, SGuint axis, float position);
		void SG_EXPORT (*move)(void* joystick, float* axis);
	} SGCoreJoystickCallbacks;

	typedef struct SGCoreKeyboardCallbacks
	{
		void SG_EXPORT (*key)(void* keyboard, SGuint key, SGbool down);
		void SG_EXPORT (*chr)(void* keyboard, SGdchar chr, SGbool down);
	} SGCoreKeyboardCallbacks;

	typedef struct SGCoreMouseCallbacks
	{
		void SG_EXPORT (*button)(void* mouse, SGuint button, SGbool down);
		void SG_EXPORT (*move)(void* mouse, SGint x, SGint y);
		void SG_EXPORT (*wheel)(void* mouse, SGint w);
	} SGCoreMouseCallbacks;

typedef struct SGModuleInput
{
	/**
	 * \name Joystick
	 */
	/// @{
	SGuint SG_EXPORT (*sgmCoreJoystickGetNumJoysticks)(void* window, size_t* numjoys);
	SGuint SG_EXPORT (*sgmCoreJoystickCreate)(void** joystick, void* window, SGuint id);
	SGuint SG_EXPORT (*sgmCoreJoystickDestroy)(void* joystick);
	SGuint SG_EXPORT (*sgmCoreJoystickGetID)(void* joystick, SGuint* id);
	SGuint SG_EXPORT (*sgmCoreJoystickGetNumButtons)(void* joystick, size_t* numbuttons);
	//SGuint SG_EXPORT (*sgmCoreJoystickSetButtons)(void* joystick, SGbool* state);
	SGuint SG_EXPORT (*sgmCoreJoystickGetButtons)(void* joystick, SGbool* state);
	SGuint SG_EXPORT (*sgmCoreJoystickGetNumAxis)(void* joystick, size_t* numaxis);
	//SGuint SG_EXPORT (*sgmCoreJoystickSetAxis)(void* joystick, float* position);
	SGuint SG_EXPORT (*sgmCoreJoystickGetAxis)(void* joystick, float* position);

	SGuint SG_EXPORT (*sgmCoreJoystickSetCallbacks)(void* joystick, SGCoreJoystickCallbacks* callbacks);
	//SGuint SG_EXPORT (*sgmCoreJoystickGetCallbacks)(void* joystick, SGCoreJoystickCallbacks** callbacks);
	/// @}

	/**
	 * \name Keyboard
	 */
	/// @{
	SGuint SG_EXPORT (*sgmCoreKeyboardCreate)(void** keyboard, void* window);
	SGuint SG_EXPORT (*sgmCoreKeyboardDestroy)(void* keyboard);
	//SGuint SG_EXPORT (*sgmCoreKeyboardSetKey)(void* keyboard, SGuint key, SGbool down);
	SGuint SG_EXPORT (*sgmCoreKeyboardGetKey)(void* keyboard, SGuint key, SGbool* down);
	//SGuint SG_EXPORT (*sgmCoreKeyboardSetChr)(void* keyboard, SGuint chr, SGbool down);
	//SGuint SG_EXPORT (*sgmCoreKeyboardGetChr)(void* keyboard, dchar chr, SGbool* down);

	SGuint SG_EXPORT (*sgmCoreKeyboardSetCallbacks)(void* keyboard, SGCoreKeyboardCallbacks* callbacks);
	//SGuint SG_EXPORT (*sgmCoreKeyboardGetCallbacks)(void* keyboard, SGCoreKeyboardCallbacks** callbacks);
	/// @}

	/**
	 * \name Mouse
	 */
	/// @{
	SGuint SG_EXPORT (*sgmCoreMouseCreate)(void** mouse, void* window);
	SGuint SG_EXPORT (*sgmCoreMouseDestroy)(void* mouse);
	// should these two [sgmCoreMouseShow,sgmCoreMouseHide] be put into a single function?
	SGuint SG_EXPORT (*sgmCoreMouseShow)(void* mouse);
	SGuint SG_EXPORT (*sgmCoreMouseHide)(void* mouse);
	//SGuint SG_EXPORT (*sgmCoreMouseIsShown)(void* mouse, SGbool* shown);
	//SGuint SG_EXPORT (*sgmCoreMouseIsHidden)(void* mouse, SGbool* hidden);
	SGuint SG_EXPORT (*sgmCoreMouseGetNumButtons)(void* mouse, SGuint* numbuttons);
	//SGuint SG_EXPORT (*sgmCoreMouseSetButtons)(void* mouse, SGbool* state);
	SGuint SG_EXPORT (*sgmCoreMouseGetButtons)(void* mouse, SGbool* state);
	SGuint SG_EXPORT (*sgmCoreMouseSetPosition)(void* mouse, int x, int y);
	SGuint SG_EXPORT (*sgmCoreMouseGetPosition)(void* mouse, int* x, int* y);
	//SGuint SG_EXPORT (*sgmCoreMouseSetWheel)(void* mouse, int w);
	SGuint SG_EXPORT (*sgmCoreMouseGetWheel)(void* mouse, int* w);

	SGuint SG_EXPORT (*sgmCoreMouseSetCallbacks)(void* mouse, SGCoreMouseCallbacks* callbacks);
	//SGuint SG_EXPORT (*sgmCoreMouseGetCallbacks)(void* mouse, SGCoreMouseCallbacks** callbacks);
	/// @}
} SGModuleInput;

#ifdef SG_BUILD_LIBRARY
SGModuleInput _sg_modInput;
#endif // SG_BUILD_LIBRARY

void SG_EXPORT _sgModuleLoadInput(SGLibrary* lib);

SGModuleInput* SG_EXPORT sgModuleGetInput(void);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_MODULES_INPUT_H__
