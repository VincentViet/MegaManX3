#ifndef WALL_H
#define WALL_H

#include "object.h"

class Wall : public Object
{
public:
	explicit Wall(Vec2 pos, float32 width, float32 height);

	void Start() override;
	void Update() override;
	void Draw() override;
	void OnColliderEnter(Object* collider) override;
	void OnColliderExit(Object* collider) override;
	Rect& GetBound() override;

private:
	float32 half_width;
	float32 half_height;
};

#endif // WALL_H
