#ifndef PHYSICS_H
#define PHYSICS_H

#include "box2D.h"

Rigidbody*	azorCreateBody(BodyDecs* body_decs, ColliderDecs* col_decs);
void		azorUpdatePhysics(void);
void		azorDestroyPhysics(void);

#endif // PHYSICS_H
