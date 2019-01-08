#ifndef SPAWNER_H
#define SPAWNER_H

#include "../bullets/bullet.h"
#include <vector>

class Spawner
{
public:
	Spawner() = default;
	virtual ~Spawner() = default;

	void Update();

	virtual void Shoot() const = 0;

	Object* owner{};
	Vec2 offset;
protected:
	Vec2 position;
	std::vector<Bullet*> bullets_;
private:
};

#endif // SPAWNER_H
