#include "blasthornet.h"
#include "states/blasthornet_states.h"
#include <physics/polygon_shape.h>
#include "window.h"
#include "camera.h"
#include "debug.h"

static AZORcamera g_camera;


Blasthornet::Blasthornet()
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

	State::blasthornet_idle = new BlasthornetIdleState;
	State::blasthornet_sting = new BlasthornetStingState;
	State::blasthornet_call = new BlasthornetCallState;
	State::blasthornet_exploded = new BlasthornetExplodeState;

	tag = Tag::ENEMY;
	ChangeState(State::blasthornet_idle);

	g_camera = azorGetCamera();
}

Blasthornet::~Blasthornet()
{
	delete State::blasthornet_idle;
	delete State::blasthornet_sting;
	delete State::blasthornet_call;
	delete State::blasthornet_exploded;
}

void Blasthornet::Start()
{

}

void Blasthornet::Update()
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

void Blasthornet::Draw()
{
	state->Draw();
}

void Blasthornet::OnColliderEnter(Object* collider)
{
	if (collider->tag == Tag::BULLET)
	{
		ChangeState(State::blasthornet_exploded);
	}
}

void Blasthornet::OnColliderExit(Object* collider)
{
}

Rect& Blasthornet::GetBound()
{
	static Rect result;
	result.left = position.x - (37.0f / 2);
	result.top = position.y - (37.0f / 2);
	result.right = position.x + (39.0f / 2);
	result.bottom = position.y + (39.0f / 2);
	return result;
}