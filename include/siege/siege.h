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
 * \file siege.h
 * \brief Main siege file, acting as sort of a glue for the rest.
 */

#ifndef __SIEGE_H__
#define __SIEGE_H__

#include "common.h"

#include "ai/astar.h"
#include "ai/grid.h"
#include "audio/buffer.h"
#include "audio/source.h"
#include "core/console.h"
#include "core/core.h"
#include "core/entity.h"
#include "core/event.h"
#include "core/window.h"
#include "graphics/draw.h"
#include "graphics/emitter.h"
#include "graphics/font.h"
#include "graphics/image.h"
#include "graphics/light.h"
#include "graphics/mask.h"
#include "graphics/sprite.h"
#include "graphics/surface.h"
#include "graphics/texture.h"
#include "graphics/trail.h"
#include "graphics/turtle.h"
#include "graphics/viewport.h"
#include "input/keyboard.h"
#include "input/mouse.h"
#include "input/joystick.h"
#include "modules/audio.h"
#include "modules/fonts.h"
#include "modules/graphics.h"
#include "modules/input.h"
#include "modules/modules.h"
#include "modules/physics.h"
#include "modules/window.h"
#include "physics/body.h"
#include "physics/collision.h"
#include "physics/constraint.h"
#include "physics/shape.h"
#include "physics/space.h"
#include "util/file/json.h"
#include "util/thread/key.h"
#include "util/thread/mutex.h"
#include "util/thread/semaphore.h"
#include "util/thread/thread.h"
#include "util/angle.h"
#include "util/color.h"
#include "util/conv.h"
#include "util/directory.h"
#include "util/gradient.h"
#include "util/link.h"
#include "util/list.h"
#include "util/matrix.h"
#include "util/rand.h"
#include "util/string.h"
#include "util/time.h"
#include "util/tree.h"
#include "util/vector.h"

#endif // __SIEGE_H__
