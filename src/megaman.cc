#include "megaman.h"
#include "states/megaman_states.h"
#include <physics/polygon_shape.h>
#include "window.h"
#include "camera.h"

static AZORwindow g_window;
static AZORcamera g_camera;

Megaman::Megaman()
{
	this->position = Vec2{ 100, 900 };
	body_decs.position = b2Vec2{ 100, 930 };
	body_decs.type = BodyType::DYNAMIC;
	body_decs.fixedRotation = true;
	body_decs.userData = this;
	body_decs.gravityScale = 0;

	const auto box = new PolygonShape;
	box->SetAsBox(15, 17);
	collider_decs.shape = box;
	collider_decs.density = 1.0f;
	collider_decs.friction = 1.0f;
	collider_decs.restitution = 0.0f;
	collider_decs.userData = this;

	State::megaman_idle = new MegamanIdle;
	State::megaman_run = new MegamanRun;
	State::megaman_jump = new MegamanJump;
	State::megaman_shoot = new MegamanShoot;
	State::megaman_dash = new MegamanDash;

	tag = Tag::PLAYER;
	ChangeState(State::megaman_idle);

	g_window = azorGetWindow();
	g_camera = azorGetCamera();
}

Megaman::~Megaman()
{
	delete State::megaman_idle;
	delete State::megaman_run;
	delete State::megaman_jump;
	delete State::megaman_shoot;
	delete State::megaman_dash;
}

void Megaman::Start()
{
	
}

void Megaman::Update()
{
	static Vec2 pos;

	Object::Update();

	if (g_camera->is_follwing_x)
		pos.x = g_window->width * 0.5f;
	else
		pos.x = this->position.x - g_camera->bound.left;

	if (g_camera->is_follwing_y)
		pos.y = g_window->height * 0.5f;
	else
		pos.y = this->position.y - g_camera->bound.top;

	this->body->SetTransform(pos, 0.0f);

	state->Update();
}

void Megaman::Draw()
{
	state->Draw();
}

void Megaman::OnColliderEnter(Object* collider)
{
	if (collider->tag == Tag::GROUND)
	{
		if (is_jumping)
		{
			this->vel.y = 0.0f;
			this->vel.x = 0.0f;
			is_jumping = false;
			ChangeState(State::megaman_idle);
		}
	}
}

void Megaman::OnColliderExit(Object* collider)
{
	if (collider->tag == Tag::GROUND)
	{
		if (!is_jumping)
		{
			is_jumping = true;
			ChangeState(State::megaman_jump);
		}
	}
}



