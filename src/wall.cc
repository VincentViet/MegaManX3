#include "wall.h"

Wall::Wall(Vec2 pos, float32 width, float32 height)
	: Object(Tag::WALL), half_width(width * 0.5f), half_height(height * 0.5f)
{

}

void Wall::Start()
{
}

void Wall::Update()
{
}

void Wall::Draw()
{
}

void Wall::OnColliderEnter(Object* collider)
{
}

void Wall::OnColliderExit(Object* collider)
{
}

Rect& Wall::GetBound()
{
	static Rect result;
	result.left = position.x - half_width;
	result.top = position.y - half_height;
	result.right = position.x + half_width;
	result.bottom = position.y + half_height;
	return result;
}
