#ifndef WORLD_H
#define WORLD_H

#include "rigidbody.h"
#include "quad_tree.h"

typedef class World
{
public:
	World();
	~World();
	AZORbody CreateBody(BodyDecs* decs);
	void Update(float32 time_step);
protected:
private:
	QuadTree* tree_;
	BodyList	dynamic_;
	BodyList	bodies_;
	float32 gravity_;
} World, *AZORworld;

#endif // WORLD_H

