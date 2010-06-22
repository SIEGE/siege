#ifndef __SIEGE_BACKEND_H__
#define __SIEGE_BACKEND_H__

#include "backend/module.h"
/// Graphics
#include "backend/graphics/context.h"
#include "backend/graphics/draw.h"
#include "backend/graphics/surface.h"
#include "backend/graphics/texture.h"
#include "backend/graphics/viewport.h"
/// Graphics Load
#include "backend/graphics/load.h"
/// Audio
#ifdef SG_LEGACY_API
#include "backend/audio/sample.h"
#else
#include "backend/audio/buffer.h"
#endif // SG_LEGACY_API
#include "backend/audio/source.h"
/// Audio Load
#include "backend/audio/load.h"
/// Input
#include "backend/core/joystick.h"
#include "backend/core/keyboard.h"
#include "backend/core/mouse.h"
/// Windowing
#include "backend/core/window.h"
/// Fonts
#include "backend/fonts/face.h"
#include "backend/fonts/chars.h"
/// Physics
#include "backend/physics/body.h"
#include "backend/physics/constraint.h"
#include "backend/physics/shape.h"
#include "backend/physics/space.h"

/// Test (things in a state of flux, will be removed or at least renamed)
#ifdef SIEGE_TEST
#   include "backend/physics/test.h"
#endif // SIEGE_TEST

#include "backend/debug.h"

#endif // __SIEGE_BACKEND_H__