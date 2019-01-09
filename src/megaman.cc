#include "megaman.h"
#include "states/megaman_states.h"
#include <physics/polygon_shape.h>
#include "window.h"
#include "camera.h"
#include "debug.h"

static AZORwindow g_window;
static AZORcamera g_camera;

Megaman::Megaman()
{
	body_decs.position = b2Vec2{ 50, 450 };
	body_decs.type = BodyType::DYNAMIC;
	body_decs.fixedRotation = true;
	body_decs.userData = this;
	body_decs.gravityScale = 1;

	const auto box = new PolygonShape;
	box->SetAsBox(15, 17);
	collider_decs.shape = box;
	collider_decs.density = 1.0f;
	collider_decs.friction = 0.0f;
	collider_decs.restitution = 0.0f;
	collider_decs.userData = this;

	State::megaman_idle = new MegamanIdle;
	State::megaman_run = new MegamanRun;
	State::megaman_jump = new MegamanJump;
	State::megaman_shoot = new MegamanShoot;
	State::megaman_dash = new MegamanDash;
	State::megaman_climb = new MegamanClimb;

	tag = Tag::PLAYER;
	ChangeState(State::megaman_idle);

	is_touch_ground = false;

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
	delete State::megaman_climb;
}

void Megaman::Start()
{
	
}

void Megaman::Update()
{
	static Vec2 old_pos;
	static Vec2 pos;
	// Object::Update();

	// if (g_camera->is_follwing_x)
	// 	pos.x = g_window->width * 0.5f;
	// else
	// 	pos.x = this->position.x - g_camera->bound.left;
	//
	// if (g_camera->is_follwing_y)
	// 	pos.y = g_window->height * 0.5f;
	// else
	// 	pos.y = this->position.y - g_camera->bound.top;

	pos = body->GetPosition();

	if (g_camera->is_follwing_x)
		// pos.x = g_window->width * 0.5f;
		if (b2Abs(pos.x - old_pos.x) < 0.5)
			g_camera->offset_x = 0.0f;
		else { g_camera->offset_x = pos.x - old_pos.x; }
	else
		position.x = /*pos.x*/ pos.x /*+ g_camera->bound.left*/;
	
	if (g_camera->is_follwing_y)
		// pos.y = g_window->height * 0.5f;
		if (b2Abs(pos.y - old_pos.y) < 0.5)
			g_camera->offset_y = 0.0f;
		else { g_camera->offset_y = pos.y - old_pos.y; }
	else
		position.y = /*pos.y*/pos.y /*+ g_camera->bound.top*/;

	position.x = /*pos.x*/ pos.x + g_camera->bound.left;
	position.y = /*pos.y*/pos.y + g_camera->bound.top;

	// this->body->SetTransform(pos, 0.0f);

	// Debug::Log("x: %0.2f, y: %0.2f\n", position.x, position.y);

	old_pos = body->GetPosition();

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
			// this->vel.y = 0.0f;
			// this->vel.x = 0.0f;
			body->SetLinearVelocity(Vec2{ 0, 0 });
			is_jumping = false;
			ChangeState(State::megaman_idle);
		}

		is_touch_ground = true;
	}

	if (collider->tag == Tag::WALL)
	{
		// this->vel.x = 0;
		// is_touch_wall = true;
		if (!is_touch_ground)
		{
			// direction = -direction;
			is_jumping = false;
			ChangeState(State::megaman_climb);
		}
	}
}

void Megaman::OnColliderExit(Object* collider)
{
	static Vec2 collider_pos;
	static Vec2 pos;

	if (collider->tag == Tag::GROUND)
	{
		pos = this->body->GetPosition();
		collider_pos = collider->body->GetPosition();
		const float32 offset = pos.y - collider_pos.y;
		if (!is_jumping && (offset > 0.5f))
		{
			is_jumping = true;
			ChangeState(State::megaman_jump);
		}

		is_touch_ground = false;
	}
}



