#ifndef SPAWNER_H
#define SPAWNER_H

#include "../bullets/bullet.h"

enum class BulletType
{
	SMALL_BUSTER,
	MEDIUM_BUSTER,
	LARGE_BUSTER
};

class Spawner
{
public:
	Spawner() = default;
	virtual ~Spawner() = default;

	void Update();

	virtual void Shoot(BulletType type) = 0;

	Object* owner{};
	Vec2 offset;
protected:
	Vec2 position;
private:
};

#endif // SPAWNER_H
