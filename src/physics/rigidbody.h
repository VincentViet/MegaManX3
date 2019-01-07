#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "aabb.h"

enum class BodyType
{
	STATIC,
	DYNAMIC
};

struct BodyDecs
{
	Vec2 pos;
	Vec2 vel;
	float32 width;
	float32 height;
	BodyType type;
	void* object;
};

typedef class Rigidbody
{
	friend class World;
public:
	AABB GetAABB() const;

	BodyType type;
	Vec2 vel;
	Vec2 pos;
	float32 width;
	float32 height;
	void* object;
protected:
	explicit Rigidbody(BodyDecs* decs);
	~Rigidbody() = default;
private:
} Rigidbody, *AZORbody;

#endif // RIGIDBODY_H

