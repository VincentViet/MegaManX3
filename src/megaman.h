#ifndef MEGAMAN_H
#define MEGAMAN_H

#include "object.h"

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
};

#endif // MEGAMAN_H
