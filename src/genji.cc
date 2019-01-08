#include "genji.h"
#include "states/genji_states.h"
#include <physics/polygon_shape.h>
#include "window.h"
#include "camera.h"
#include "debug.h"

static AZORcamera g_camera;


Genji::Genji()
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

	State::genji_idle = new GenjiIdleState;
	State::genji_rotate = new GenjiRotateState;
	State::genji_exploded = new GenjiExplodeState;

	tag = Tag::ENEMY;
	ChangeState(State::genji_idle);

	g_camera = azorGetCamera();
}

Genji::~Genji()
{
	delete State::genji_idle;
	delete State::genji_rotate;
	delete State::genji_exploded;
}

void Genji::Start()
{

}

void Genji::Update()
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

void Genji::Draw()
{
	state->Draw();
}

void Genji::OnColliderEnter(Object* collider)
{
	if (collider->tag == Tag::BULLET)
	{
		ChangeState(State::genji_exploded);
	}
}

void Genji::OnColliderExit(Object* collider)
{
}

Rect& Genji::GetBound()
{
	static Rect result;
	result.left = position.x - (37.0f / 2);
	result.top = position.y - (37.0f / 2);
	result.right = position.x + (39.0f / 2);
	result.bottom = position.y + (39.0f / 2);
	return result;
}