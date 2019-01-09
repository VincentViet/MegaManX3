#include "elevator.h"
#include "camera.h"
#include <physics/polygon_shape.h>
#include "debug.h"

static AZORcamera g_camera;

Elevator::Elevator()
{
	position = Vec2{ 890, 970 };
	// body_decs.position = Vec2{ 785,  };
	body_decs.type = BodyType::STATIC;
	body_decs.fixedRotation = true;
	body_decs.userData = this;
	body_decs.gravityScale = 0;

	const auto box = new PolygonShape;
	box->SetAsBox(40, 15);
	collider_decs.shape = box;
	collider_decs.density = 1.0f;
	collider_decs.friction = 1.0f;
	collider_decs.restitution = 0.0f;
	collider_decs.userData = this;

	tag = Tag::ELEVATOR;
	is_active = false;

	g_camera = azorGetCamera();
	static Rect rect{ 5, 4, 101, 48 };
	sprite_ = new Sprite("elevator", &rect);
	direction = 1;
}

Elevator::~Elevator() = default;

void Elevator::Start()
{

}

void Elevator::Update()
{
	static Vec2 pos;
	// static float32 delay = 2;
	if (is_active)
	{
		position.y += Debug::delta_time * -50.0f;
		if (pos.y < 100.0f)
		{
			is_active = false;
			// direction = -direction;
		}
	}

	pos.x = position.x - g_camera->bound.left;
	pos.y = position.y - g_camera->bound.top;
	body->SetTransform(pos, 0.0f);

	// Debug::Log("%d\n", g_camera->bound.top);
	// position.x = pos.x + g_camera->bound.left;
	// position.y = pos.y + g_camera->bound.top;
}

void Elevator::Draw()
{
	sprite_->Draw(0, position, direction);
}

void Elevator::OnColliderEnter(Object* collider)
{
	// static float32 delay = 2;
	if (collider->tag == Tag::PLAYER)
	{
		// delay -= Debug::delta_time;
		// if (delay < 0.0f)
		// {
		// 	this->is_active = true;
		// }
		this->is_active = true;
	}
}

void Elevator::OnColliderExit(Object* collider)
{
}
