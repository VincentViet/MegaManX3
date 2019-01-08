#ifndef SMALL_BUSTER_SPAWNER_H
#define SMALL_BUSTER_SPAWNER_H

#include "spawner.h"

class SmallBusterSpawner : public Spawner
{
public:
	SmallBusterSpawner(Vec2 offset, Object* owner);
	~SmallBusterSpawner();

	void Shoot() const override;
protected:
private:
};

#endif // SMALL_BUSTER_SPAWNER_H
