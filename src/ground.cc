#include "ground.h"
#include "window.h"
#include "camera.h"
#include <physics/polygon_shape.h>

static AZORwindow g_window;
static AZORcamera g_camera;

Ground::Ground(Vec2 pos, float32 width, float32 height)
	: Object(Tag::GROUND), half_width(width * 0.5f), half_height(height * 0.5f)
{
	this->position = pos;
	body_decs.position = pos;
	body_decs.type = BodyType::STATIC;
	body_decs.fixedRotation = true;
	body_decs.userData = this;
	body_decs.gravityScale = 0;

	const auto box = new PolygonShape;
	box->SetAsBox(half_width, half_height);
	collider_decs.shape = box;
	collider_decs.density = 1.0f;
	collider_decs.friction = 1.0f;
	collider_decs.restitution = 0.0f;
	collider_decs.userData = this;

	g_window = azorGetWindow();
	g_camera = azorGetCamera();
}

void Ground::Start()
{
}

void Ground::Update()
{
	static Vec2 pos;

	if (g_camera->IsContained(this))
	{
		pos.x = this->position.x - g_camera->bound.left;
		pos.y = this->position.y - g_camera->bound.top;
		this->body->SetTransform(pos, 0.0f);

		this->body->GetFixtureList()[0].SetSensor(false);
	}
	else { /*this->body->GetFixtureList()[0].SetSensor(true);*/ }
}

void Ground::Draw()
{
}

void Ground::OnColliderEnter(Object* collider)
{
}

void Ground::OnColliderExit(Object* collider)
{
}

Rect& Ground::GetBound()
{
	static Rect result;
	result.left = position.x - half_width;
	result.top = position.y - half_height;
	result.right = position.x + half_width;
	result.bottom = position.y + half_height;
	return result;
}
