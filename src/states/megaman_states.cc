#include "megaman_states.h"
#include "../input.h"
#include "../megaman.h"
#include "../debug.h"
#include <vector>

MegamanIdle* State::megaman_idle;
MegamanRun*	State::megaman_run;
MegamanJump* State::megaman_jump;
MegamanShoot* State::megaman_shoot;
MegamanDash* State::megaman_dash;
MegamanClimb* State::megaman_climb;

#pragma region Idle
MegamanIdle::MegamanIdle()
{
	static std::vector<Rect> rects
	{
		{323, 17, 323 + 30, 17 + 34},
		{357, 17, 357 + 30, 17 + 34},
		{391, 17, 391 + 30, 17 + 34}
	};

	delay_ = 5;

	sprite_ = new Sprite(MEGAMAN_ALIAS, rects.data());
}

MegamanIdle::~MegamanIdle()
{
	delete sprite_;
}

void MegamanIdle::Update()
{
	static Megaman* megaman;
	static float32 delay = 1.0f;

	megaman = static_cast<Megaman*>(this->owner);
	if (azorIsKeyDown(Keys::LEFTARROW))
	{
		megaman->ChangeState(State::megaman_run);
	}
	else if (azorIsKeyDown(Keys::RIGHTARROW))
	{
		megaman->ChangeState(State::megaman_run);
	}
	else if (azorIsKeyDown(Keys::KEY_X)/* && delay < 0.0f*/)
	{
		megaman->ChangeState(State::megaman_jump);
		delay = 1.0f;
	}
	else if (azorIsKeyDown(Keys::KEY_C))
	{
		megaman->ChangeState(State::megaman_shoot);
	}
	else if (azorIsKeyDown(Keys::KEY_Z)/* && delay < 0.0f*/)
	{
		megaman->ChangeState(State::megaman_dash);
		// delay = 1.0f;
	}
	else { delay -= Debug::delta_time; }
}

void MegamanIdle::Draw()
{
	static uint8 index = 0;
	static float32 f = 0.0f;
	static Megaman* megaman;
	// static AZORcamera g_camera;

	// g_camera = azorGetCamera();
	megaman = static_cast<Megaman*>(this->owner);
	if (f < Debug::total_time)
	{
		index++;
		f = Debug::total_time + Debug::delta_time * delay_;

		if (index == 3)
			index = 0;
	}

	sprite_->Draw(index, megaman->GetPosition(), megaman->direction);
}

#pragma endregion

#pragma region Run
MegamanRun::MegamanRun()
{
	static std::vector<Rect> rects
	{
		// normal run
		{106, 107, 106 + 30, 107 + 34},
		{137, 107, 137 + 20, 107 + 34},
		{158, 106, 158 + 23, 106 + 35},

		{181, 107, 181 + 32, 107 + 34},
		{213, 108, 213 + 34, 108 + 33},
		{247, 108, 247 + 26, 108 + 33},

		{276, 107, 276 + 22, 107 + 34},
		{298, 106, 298 + 25, 106 + 35},
		{326, 107, 326 + 30, 107 + 34},

		{357, 108, 357 + 34, 108 + 33},
		{391, 108, 391 + 29, 107 + 33},

		// run shoot
		{61, 192, 61 + 35, 192 + 34},
		{97, 193, 97 + 29, 193 + 34},
		{126, 192, 126 + 32, 192 + 35},
		{158, 193, 158 + 35, 193 + 34},
		{195, 194, 195 + 37, 194 + 33},
		{233, 194, 233 + 34, 194 + 33},
		{267, 193, 267 + 31, 193 + 34},
		{298, 192, 298 + 33, 192 + 35},
		{331, 193, 331 + 35, 193 + 34},
		{367, 194, 367 + 37, 194 + 33},
		{404, 194, 404 + 35, 194 + 33}
	};

	delay_ = 5;
	sprite_ = new Sprite(MEGAMAN_ALIAS, rects.data());
	is_shooting = false;
}

MegamanRun::~MegamanRun()
{
	delete sprite_;
}

void MegamanRun::Update()
{
	static Megaman* megaman;
	static Vec2 vel;
	megaman = static_cast<Megaman*>(this->owner);

	vel = megaman->body->GetLinearVelocity();
	if (azorIsKeyDown(Keys::LEFTARROW))
	{
		megaman->direction = -1;
		megaman->body->SetLinearVelocity(Vec2{ -50, vel.y });
		// megaman->vel.x = -100;
		if (azorIsKeyDown(Keys::KEY_X))
		{
			megaman->ChangeState(State::megaman_jump);
		}
		else if (azorIsKeyDown(Keys::KEY_C))
		{
			is_shooting = true;
		}
		else if (azorIsKeyDown(Keys::KEY_Z))
		{
			megaman->ChangeState(State::megaman_dash);
		}
		else
		{
			is_shooting = false;
		}

		return;
	}

	if (azorIsKeyDown(Keys::RIGHTARROW))
	{
		megaman->direction = 1;
		megaman->body->SetLinearVelocity(Vec2{ 50, vel.y });
		// megaman->vel.x = 100;
		if (azorIsKeyDown(Keys::KEY_X))
		{
			megaman->ChangeState(State::megaman_jump);
		}
		else if (azorIsKeyDown(Keys::KEY_C))
		{
			is_shooting = true;
		}
		else if (azorIsKeyDown(Keys::KEY_Z))
		{
			megaman->ChangeState(State::megaman_dash);
		}
		else
		{
			is_shooting = false;
		}
		return;
	}

	megaman->body->SetLinearVelocity(Vec2{0, 0});
	megaman->ChangeState(State::megaman_idle);
}

void MegamanRun::Draw()
{
	static uint8 index = 0;
	static uint8 offset = 0;
	static float32 f = 0.0f;
	static Megaman* megaman;

	megaman = static_cast<Megaman*>(this->owner);
	if (f < Debug::total_time)
	{
		index++;
		f = Debug::total_time + Debug::delta_time * delay_;

		if (index == 11)
			index = 0;

		if (is_shooting)
			offset = 11;
		else { offset = 0; }
	}

	sprite_->Draw(index + offset, megaman->GetPosition(), megaman->direction);
	// Debug::Log("%d\n", index + offset);
}
#pragma endregion

#pragma region Jump
MegamanJump::MegamanJump()
{
	static std::vector<Rect> rects
	{
		//normal jump
		{202, 53, 226, 100},
		{229, 53, 246, 100},
		{250, 53, 271, 100},
		{273, 53, 296, 100},
		{297, 53, 325, 100},
		//jump shoot
		{66, 152, 66 + 29, 152 + 37},
		{97, 148, 97 + 24, 148 + 41},
		{121, 143, 121 + 27, 143 + 46},
		{148, 148, 148 + 32, 148 + 41},
		{181, 147, 181 + 31, 147 + 42}
	};

	delay_ = 5;
	sprite_ = new Sprite(MEGAMAN_ALIAS, rects.data());
	is_shooting = false;
}

MegamanJump::~MegamanJump()
{
	delete sprite_;
}

void MegamanJump::Update()
{
	static Megaman* megaman;
	static Vec2 vel;

	megaman = static_cast<Megaman*>(this->owner);
	vel = megaman->body->GetLinearVelocity();
	if (!megaman->is_jumping)
	{
		// megaman->vel.y = -150;
		vel.y = -400;
		megaman->is_jumping = true;
	}

	if (azorIsKeyDown(Keys::LEFTARROW))
	{
		megaman->direction = -1;
		vel.x = -50;
		// megaman->vel.x = -100;
	}
	else if (azorIsKeyDown(Keys::RIGHTARROW))
	{
		megaman->direction = 1;
		vel.x = 50;
		// megaman->vel.x = 100;
	}

	megaman->body->SetLinearVelocity(vel);

	if (azorIsKeyDown(Keys::KEY_C))
	{
		is_shooting = true;
	}
	else
	{
		is_shooting = false;
	}
}

void MegamanJump::Draw()
{
	static uint8 index = 0;
	static uint8 offset = 0;
	static float32 f = 0.0f;
	static Megaman* megaman;
	// static AZORcamera g_camera;

	// g_camera = azorGetCamera();
	megaman = static_cast<Megaman*>(this->owner);
	if (f < Debug::total_time)
	{
		index++;
		f = Debug::total_time + Debug::delta_time * delay_;

		if (index == 5)
			index = 4;

		if (is_shooting)
			index = 9;
		else { index = 4; }
	}

	sprite_->Draw(index + offset, megaman->GetPosition(), megaman->direction);
}
#pragma endregion

#pragma region Shoot
MegamanShoot::MegamanShoot()
{
	static std::vector<Rect> rects
	{
		{133, 66, 133 + 30, 66 + 34},
		{168, 66, 168 + 30, 66 + 34}
	};

	delay_ = 5;
	sprite_ = new Sprite(MEGAMAN_ALIAS, rects.data());
}

MegamanShoot::~MegamanShoot()
{
	delete sprite_;
}

void MegamanShoot::Update()
{
	static Megaman* megaman;

	megaman = static_cast<Megaman*>(this->owner);
	if (azorIsKeyDown(Keys::KEY_C))
	{
		
	}
	else
	{
		megaman->ChangeState(State::megaman_idle);
	}
}

void MegamanShoot::Draw()
{
	static uint8 index = 0;
	static float32 f = 0.0f;
	static Megaman* megaman;

	megaman = static_cast<Megaman*>(this->owner);
	if (f < Debug::total_time)
	{
		index++;
		f = Debug::total_time + Debug::delta_time * delay_;

		if (index == 2)
			index = 0;
	}

	sprite_->Draw(index, megaman->GetPosition(), megaman->direction);
}
#pragma endregion

#pragma region Dash
MegamanDash::MegamanDash()
{
	static std::vector<Rect> rects
	{
		//normal dash
		{285, 158, 285 + 28, 158 + 31},
		{317, 163, 317 + 38, 163 + 26},

		//dash shoot
		{361, 158, 361 + 38, 158 + 31},
		{404, 163, 404 + 49, 163 + 26}
	};

	delay_ = 5;
	sprite_ = new Sprite(MEGAMAN_ALIAS, rects.data());
	is_shooting = false;
}

MegamanDash::~MegamanDash()
{
	delete sprite_;
}

void MegamanDash::Update()
{
	static Megaman* megaman;
	static Vec2 vel;
	static float32 charge_time = 0.3f;
	megaman = static_cast<Megaman*>(this->owner);
	vel = megaman->body->GetLinearVelocity();
	if (azorIsKeyDown(Keys::KEY_Z) && charge_time > 0.0f)
	{
		// megaman->vel.x = 300 * megaman->direction;
		vel.x = 300 * megaman->direction;
		if (azorIsKeyDown(Keys::KEY_X))
		{
			megaman->ChangeState(State::megaman_jump);
		}else if (azorIsKeyDown(Keys::KEY_C))
		{
			is_shooting = true;
		}
		else { is_shooting = false; }

		charge_time -= Debug::delta_time;
		// Debug::Log("%0.2f\n", charge_time);
	}
	else
	{
		charge_time = 0.3f;
		// megaman->vel.x = 0;
		vel.x = 0.0f;
		megaman->ChangeState(State::megaman_idle);
	}

	megaman->body->SetLinearVelocity(vel);
}

void MegamanDash::Draw()
{
	static uint8 index = 0;
	static uint8 offset = 0;
	static float32 f = 0.0f;
	static Megaman* megaman;

	megaman = static_cast<Megaman*>(this->owner);
	if (f < Debug::total_time)
	{
		index++;
		f = Debug::total_time + Debug::delta_time * delay_;

		if (index == 2)
			index = 1;

		if (is_shooting)
			offset = 2;
		else { offset = 0; }
	}

	sprite_->Draw(index + offset, megaman->GetPosition(), megaman->direction);
}
#pragma endregion


#pragma region Climp
MegamanClimb::MegamanClimb()
{
	static std::vector<Rect> rects
	{
		// normal climb
		{144, 527, 144 + 28, 527 + 42},

		// climb shoot
		{310, 526, 310 + 32, 526 + 42}
	};

	delay_ = 5;
	sprite_ = new Sprite(MEGAMAN_ALIAS, rects.data());
	is_shooting = false;
}

MegamanClimb::~MegamanClimb()
{
	delete sprite_;
}

void MegamanClimb::Update()
{
	static Megaman* megaman;
	static Vec2 vel;
	megaman = static_cast<Megaman*>(this->owner);
	vel = megaman->body->GetLinearVelocity();

	if (azorIsKeyDown(Keys::KEY_X))
	{
		const uint8 dir = megaman->direction;
		megaman->body->SetLinearVelocity(Vec2{ -dir * 50.0f, -dir * 200.0f });
		megaman->ChangeState(State::megaman_jump);
	}
}

void MegamanClimb::Draw()
{
	static uint8 index = 0;
	// static uint8 offset = 0;
	static float32 f = 0.0f;
	static Megaman* megaman;

	megaman = static_cast<Megaman*>(this->owner);
	if (f < Debug::total_time)
	{
		// index++;
		f = Debug::total_time + Debug::delta_time * delay_;

		// if (index == 1)
		// 	index = 0;

		if (is_shooting)
			index = 1;
		else { index = 0; }
	}

	sprite_->Draw(index, megaman->GetPosition(), megaman->direction);
}
#pragma endregion 