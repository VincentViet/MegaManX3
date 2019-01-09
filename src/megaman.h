#ifndef MEGAMAN_H
#define MEGAMAN_H

#include "object.h"
#include "spawners/buster_spawners.h"

class Megaman : public Object
{
public:
	Megaman();
	~Megaman();

	void Start() override;
	void Update() override;
	void Draw() override;
	void OnColliderEnter(Object* collider) override;
	void OnColliderExit(Object* collider) override;

	bool is_touch_ground;
	bool is_shooting;
	Spawner* spawner;
private:
};

#endif // MEGAMAN_H
