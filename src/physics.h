#ifndef PHYSICS_H
#define PHYSICS_H

#include <physics/body.h>
#include <physics/fixture.h>

typedef b2Body			Rigidbody;
typedef b2World			World;
typedef b2BodyDef		BodyDecs;
typedef b2FixtureDef	ColliderDecs;
typedef b2Shape			Shape;
typedef b2BodyType		BodyType;

typedef struct Physics
{
	Rigidbody*	CreateBody(BodyDecs* body_decs, ColliderDecs* collider_decs) const;
	void		Update(void) const;

	World* world;
} Physics, *AZORphysics;

// Rigidbody*	azorCreateBody(BodyDecs* body_decs, ColliderDecs* col_decs);
// void		azorUpdatePhysics(void);
AZORphysics azorGetPhysics(void);
void		azorDestroyPhysics(void);

#endif // PHYSICS_H
