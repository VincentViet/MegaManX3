#include "headgunner.h"
// #include "states/headgunner_states.h"
#include <physics/polygon_shape.h>
#include "window.h"
#include "camera.h"
#include "debug.h"

static AZORcamera g_camera;


Headgunner::Headgunner()
{
	body_decs.position = b2Vec2{ 200, 450 };
	body_decs.type = BodyType::DYNAMIC;
	body_decs.fixedRotation = true;
	body_decs.userData = this;
	body_decs.gravityScale = 1;

	const auto box = new PolygonShape;
	box->SetAsBox(37.0f / 2, 39.0f / 2);
	collider_decs.shape = box;
	collider_decs.density = 1.0f;
	collider_decs.friction = 0.0f;
	collider_decs.restitution = 0.0f;
	collider_decs.userData = this;

	// State::headgunner_idle = new HeadgunnerIdleState;
	// State::headgunner_shoot = new HeadgunnerShootState;
	// State::headgunner_exploded = new HeadgunnerExplodeState;

	tag = Tag::ENEMY;
	// ChangeState(State::headgunner_idle);

	g_camera = azorGetCamera();
}

Headgunner::~Headgunner()
{
	// delete State::headgunner_idle;
	// delete State::headgunner_exploded;
}

void Headgunner::Start()
{

}

void Headgunner::Update()
{
	state->Update();
	static Vec2 pos;
	if (g_camera->IsContained(this))
	{
		pos = body->GetPosition();

		position.x = /*pos.x*/ pos.x + g_camera->bound.left;
		position.y = /*pos.y*/pos.y + g_camera->bound.top;

		//this->body->GetFixtureList()[0].SetSensor(false);
	}
	else { /*this->body->GetFixtureList()[0].SetSensor(true);*/ }

}

void Headgunner::Draw()
{
	state->Draw();
}

void Headgunner::OnColliderEnter(Object* collider)
{
	if (collider->tag == Tag::BULLET)
	{
		// ChangeState(State::headgunner_exploded);
	}
}

void Headgunner::OnColliderExit(Object* collider)
{
}

Rect& Headgunner::GetBound()
{
	static Rect result;
	result.left = position.x - (37.0f / 2);
	result.top = position.y - (37.0f / 2);
	result.right = position.x + (39.0f / 2);
	result.bottom = position.y + (39.0f / 2);
	return result;
}