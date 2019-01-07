#include "rigidbody.h"

AABB Rigidbody::GetAABB() const
{
	return AABB
	{
		pos.x - width * 0.5f,
		pos.y - height * 0.5f,
		width,
		height
	};
}

Rigidbody::Rigidbody(BodyDecs* decs)
{
	type = decs->type;
	vel = decs->vel;
	pos = decs->pos;
	width = decs->width;
	height = decs->height;
	object = decs->object;
}
