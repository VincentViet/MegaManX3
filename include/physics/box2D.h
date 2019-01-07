/*
* Copyright (c) 2006-2009 Erin Catto http://www.box2d.org
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

#ifndef BOX2D_H
#define BOX2D_H

#include "common/settings.h"
#include "draw.h"
#include "timer.h"

#include "circle_shape.h"
#include "edge_shape.h"
#include "chain_shape.h"
#include "polygon_shape.h"

#include "broad_phase.h"
#include "distance.h"
#include "dynamic_tree.h"
#include "time_of_impact.h"

#include "body.h"
#include "fixture.h"
#include "world_callbacks.h"
#include "time_step.h"
#include "world.h"

#include "Contact.h"

typedef b2Body			Rigidbody;
typedef b2World			World;
typedef b2BodyDef		BodyDecs;
typedef b2FixtureDef	ColliderDecs;
typedef b2Shape			Shape;
typedef b2BodyType		BodyType;


#endif
