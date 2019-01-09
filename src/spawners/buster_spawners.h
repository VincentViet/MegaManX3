#ifndef SMALL_BUSTER_SPAWNER_H
#define SMALL_BUSTER_SPAWNER_H

#include "spawner.h"
#include <vector>

class BusterSpawner : public Spawner
{
public:
	BusterSpawner(Vec2 offset, Object* owner);
	~BusterSpawner();

	void Shoot(BulletType type) override;
protected:
private:
	void ShootSmallBuster();
	void ShootMediumBuster();
	void ShootLargeBuster();

	std::vector<Bullet*> small_busters_;
	std::vector<Bullet*> medium_busters_;
	std::vector<Bullet*> large_busters_;
};

#endif // SMALL_BUSTER_SPAWNER_H
