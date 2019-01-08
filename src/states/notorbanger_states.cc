#include "notorbanger_states.h"
#include "../notorbanger.h"
#include "../debug.h"
#include <vector>

NotorbangerIdleState*	State::notorbanger_idle;
NotorbangerJumpState*	State::notorbanger_jump;
NotorbangerShootState*	State::notorbanger_shoot;
NotorbangerExplodeState*	State::notorbanger_exploded;

#pragma region Idle
NotorbangerIdleState::NotorbangerIdleState()
{
	static std::vector<Rect> rects
	{
		{9, 118, 9 + 40, 118 + 31},
		{53, 120, 53 + 41, 120 + 29},
		{102, 118, 102 + 40, 126 + 31},
		{153, 117, 153 + 39, 117 + 32},
	};

	delay_ = 5;

	sprite_ = new Sprite(NOTORBANGER_ALIAS, rects.data());
}

NotorbangerIdleState::~NotorbangerIdleState()
{
	delete sprite_;
}

void NotorbangerIdleState::Update()
{
	static Notorbanger* notorbanger;
	notorbanger = static_cast<Notorbanger*>(this->owner);
	notorbanger->body->SetLinearVelocity(Vec2{ 0, 0 });
}

void NotorbangerIdleState::Draw()
{
	static uint8 index = 0;
	static float32 f = 0.0f;
	static Notorbanger* notorbanger;

	notorbanger = static_cast<Notorbanger*>(this->owner);
	if (f < Debug::total_time)
	{
		index++;
		f = Debug::total_time + Debug::delta_time * delay_;

		if (index == 4)
			index = 0;
	}

	sprite_->Draw(index, notorbanger->GetPosition(), notorbanger->direction);
}

#pragma endregion

#pragma region Jump
NotorbangerJumpState::NotorbangerJumpState()
{
	static std::vector<Rect> rects
	{
		{196, 108, 196 + 48, 108 + 41},
	};

	delay_ = 5;
	sprite_ = new Sprite(NOTORBANGER_ALIAS, rects.data());
}

NotorbangerJumpState::~NotorbangerJumpState()
{
	delete sprite_;
}

void NotorbangerJumpState::Update()
{
	static Notorbanger* notorbanger;
	notorbanger = static_cast<Notorbanger*>(this->owner);
	notorbanger->body->SetLinearVelocity(Vec2{ 0, 0 });
}

void NotorbangerJumpState::Draw()
{
	static Notorbanger* notorbanger;
	static uint8 index = 0;

	notorbanger = static_cast<Notorbanger*>(this->owner);

	sprite_->Draw(index, notorbanger->GetPosition(), notorbanger->direction);
}
#pragma endregion

#pragma region Shoot
NotorbangerShootState::NotorbangerShootState()
{
	static std::vector<Rect> rects
	{
		{35, 1, 35 + 39, 1 + 51},
		{76, 1, 76 + 37, 1 + 51},
		{117, 1, 117 + 34, 1 + 51},
		{161, 1, 158 + 29, 4 + 51},
	};

	delay_ = 5;
	sprite_ = new Sprite(NOTORBANGER_ALIAS, rects.data());
}

NotorbangerShootState::~NotorbangerShootState()
{
	delete sprite_;
}

void NotorbangerShootState::Update()
{
	static Notorbanger* notorbanger;
	notorbanger = static_cast<Notorbanger*>(this->owner);
	notorbanger->body->SetLinearVelocity(Vec2{ 0, 0 });
}

void NotorbangerShootState::Draw()
{
	static uint8 index = 0;
	static float32 f = 0.0f;
	static Notorbanger* notorbanger;

	notorbanger = static_cast<Notorbanger*>(this->owner);
	if (f < Debug::total_time)
	{
		index++;
		f = Debug::total_time + Debug::delta_time * delay_;

		if (index == 5)
			index = 0;
	}

	sprite_->Draw(index, notorbanger->GetPosition(), notorbanger->direction);
}
#pragma endregion

#pragma region Explode
NotorbangerExplodeState::NotorbangerExplodeState()
{
	static std::vector<Rect> rects
	{
		{16, 20, 16 + 16, 20 + 16},
		{41, 12, 41 + 32, 12 + 32},
		{81, 15, 81 + 28, 15 + 24},
		{118, 11, 118 + 30, 11 + 27},
		{158, 7, 158 + 32, 7 + 27},
		{202, 17, 202 + 32, 17 + 16}
	};

	delay_ = 5;
	sprite_ = new Sprite(EXPLODE_ALIAS, rects.data());
}

NotorbangerExplodeState::~NotorbangerExplodeState()
{
	delete sprite_;
}

void NotorbangerExplodeState::Update()
{
	static Notorbanger* notorbanger;
	notorbanger = static_cast<Notorbanger*>(this->owner);
	notorbanger->body->SetLinearVelocity(Vec2{ 0, 0 });
}

void NotorbangerExplodeState::Draw()
{
	static uint8 index = 0;
	static float32 f = 0.0f;
	static Notorbanger* notorbanger;

	notorbanger = static_cast<Notorbanger*>(this->owner);
	if (f < Debug::total_time)
	{
		index++;
		f = Debug::total_time + Debug::delta_time * delay_;

		if (index == 7)
			index = 0;
	}

	sprite_->Draw(index, notorbanger->GetPosition(), notorbanger->direction);
}
#pragma endregion
