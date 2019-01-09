#include "small_buster.h"
#include "../../camera.h"
#include <physics/polygon_shape.h>
#include "../../debug.h"

static AZORcamera g_camera;

SmallBuster::SmallBuster()
{
	body_decs.type = BodyType::DYNAMIC;
	body_decs.fixedRotation = true;
	body_decs.userData = this;
	body_decs.gravityScale = 0;
	body_decs.active = false;
	body_decs.linearDamping = 0.0f;

	const auto box = new PolygonShape;
	box->SetAsBox(6, 4);
	collider_decs.shape = box;
	collider_decs.density = 0.0f;
	collider_decs.friction = 0.0f;
	collider_decs.restitution = 0.0f;
	collider_decs.userData = this;
	collider_decs.isSensor = true;

	static Rect rect{162, 366, 170, 374};
	sprite_ = new Sprite("buster", &rect);

	g_camera = azorGetCamera();
}

void SmallBuster::Update()
{
	static Vec2 pos;
	if (body->IsActive())
	{
		pos = body->GetPosition();
		pos += Debug::delta_time * Vec2{ SMALL_BUSTER_SPEED * direction, 0.0f };
		body->SetTransform(pos, 0.0f);
		position.x = pos.x + g_camera->bound.left;
		position.y = pos.y + g_camera->bound.top;
		if (!g_camera->IsContained(this))
		{
			body->SetActive(false);
		}
	}
}

void SmallBuster::Draw()
{
	if (body->IsActive())
	{
		sprite_->Draw(0, position, direction);
	}
}

Rect& SmallBuster::GetBound()
{
	static Rect result;
	result.left = position.x - 6;
	result.top = position.y - 4;
	result.right = position.x + 6;
	result.bottom = position.y + 4;
	return result;
}
