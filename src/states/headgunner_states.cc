#include "headgunner_states.h"
#include "../headgunner.h"
#include "../debug.h"
#include <vector>

HeadgunnerIdleState*	State::headgunner_idle;
HeadgunnerShootState*	State::headgunner_shoot;
HeadgunnerExplodeState*	State::headgunner_exploded;

#pragma region Idle
HeadgunnerIdleState::HeadgunnerIdleState()
{
	static std::vector<Rect> rects
	{
		{88, 3, 88 + 38, 3 + 45}
	};

	delay_ = 5;

	sprite_ = new Sprite(HEADGUNNER_ALIAS, rects.data());
}

HeadgunnerIdleState::~HeadgunnerIdleState()
{
	delete sprite_;
}

void HeadgunnerIdleState::Update()
{
	static Headgunner* headgunner;
	headgunner = static_cast<Headgunner*>(this->owner);
	headgunner->body->SetLinearVelocity(Vec2{ 0, 0 });
}

void HeadgunnerIdleState::Draw()
{
	static uint8 index = 0;
	static Headgunner* headgunner;
	headgunner = static_cast<Headgunner*>(this->owner);

	sprite_->Draw(index, headgunner->GetPosition(), headgunner->direction);
}
#pragma endregion

#pragma region Jump
HeadgunnerShootState::HeadgunnerShootState()
{
	static std::vector<Rect> rects
	{
		{17, 54, 17 + 38, 54 + 45},
		{57, 54, 57 + 38, 54 + 45},
		{98, 54, 98 + 40, 54 + 45},
		{139, 54, 139 + 37, 54 + 45},

		{15, 107, 15 + 38, 107 + 45},
		{55, 107, 55 + 38, 107 + 45},
		{95, 107, 95 + 41, 107 + 45},
		{136, 107, 136 + 37, 107 + 45},
	};

	delay_ = 5;

	sprite_ = new Sprite(HEADGUNNER_ALIAS, rects.data());
}

HeadgunnerShootState::~HeadgunnerShootState()
{
	delete sprite_;
}

void HeadgunnerShootState::Update()
{
	static Headgunner* headgunner;
	headgunner = static_cast<Headgunner*>(this->owner);
	headgunner->body->SetLinearVelocity(Vec2{ 0, 0 });
}

void HeadgunnerShootState::Draw()
{
	static uint8 index = 0;
	static float32 f = 0.0f;
	static Headgunner* headgunner;

	headgunner = static_cast<Headgunner*>(this->owner);
	if (f < Debug::total_time)
	{
		index++;
		f = Debug::total_time + Debug::delta_time * delay_;

		if (index == 9)
			index = 0;
	}

	sprite_->Draw(index, headgunner->GetPosition(), headgunner->direction);
}
#pragma endregion

#pragma region Shoot
HeadgunnerExplodeState::HeadgunnerExplodeState()
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

HeadgunnerExplodeState::~HeadgunnerExplodeState()
{
	delete sprite_;
}

void HeadgunnerExplodeState::Update()
{
	static Headgunner* headgunner;
	headgunner = static_cast<Headgunner*>(this->owner);
	headgunner->body->SetLinearVelocity(Vec2{ 0, 0 });
}

void HeadgunnerExplodeState::Draw()
{
	static uint8 index = 0;
	static float32 f = 0.0f;
	static Headgunner* headgunner;

	headgunner = static_cast<Headgunner*>(this->owner);
	if (f < Debug::total_time)
	{
		index++;
		f = Debug::total_time + Debug::delta_time * delay_;

		if (index == 7)
			index = 0;
	}

	sprite_->Draw(index, headgunner->GetPosition(), headgunner->direction);
}
#pragma endregion
