#ifndef __SIEGE_H__
#define __SIEGE_H__

#include "common.h"

#include "module.h"
/// Graphics
#include "graphics/context.h"
#include "graphics/draw.h"
#include "graphics/surface.h"
#include "graphics/texture.h"
#include "graphics/viewport.h"
/// Graphics Load
#include "graphics/load.h"
/// Audio
#include "audio/sample.h"
#include "audio/source.h"
/// Audio Load
#include "audio/load.h"
/// Input
#include "core/joystick.h"
#include "core/keyboard.h"
#include "core/mouse.h"
/// Windowing
#include "core/window.h"
/// Fonts
#include "fonts/face.h"
#include "fonts/chars.h"
/// Physics
#include "physics/body.h"
#include "physics/constraint.h"
#include "physics/shape.h"
#include "physics/space.h"

/// Test (things in a state of flux, will be removed or at least renamed)
#ifdef SIEGE_TEST
#   include "physics/test.h"
#endif // SIEGE_TEST

#include "debug.h"

#endif // __SIEGE_H__
