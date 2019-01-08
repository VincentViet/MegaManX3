#include "helit_states.h"
#include "../helit.h"
#include "../debug.h"
#include <vector>

HelitIdleState*		State::helit_idle;
HelitExlodedState*	State::helit_exploded;

#pragma region Idle
HelitIdleState::HelitIdleState()
{
	static std::vector<Rect> rects
	{
		{9, 6, 9 + 39, 6 + 37},
		{50, 6, 50 + 27, 6 + 37},
		{80, 6, 80 + 24, 6 + 37},
		{108, 6, 108 + 24, 6 + 37},
		{137, 6, 137 + 26, 6 + 37}
	};

	delay_ = 5;

	sprite_ = new Sprite(HELIT_ALIAS, rects.data());
}

HelitIdleState::~HelitIdleState()
{
	delete sprite_;
}

void HelitIdleState::Update()
{
	static Helit* helit;
	static float32 delay = 1.0f;
	helit = static_cast<Helit*>(this->owner);
	helit->body->SetLinearVelocity(Vec2{ 0, 0 });

	delay -= Debug::delta_time;
}

void HelitIdleState::Draw()
{
	static uint8 index = 0;
	static float32 f = 0.0f;
	static Helit* helit;

	helit = static_cast<Helit*>(this->owner);
	if (f < Debug::total_time)
	{
		index++;
		f = Debug::total_time + Debug::delta_time * delay_;

		if (index == 5)
			index = 0;
	}

	sprite_->Draw(index, helit->GetPosition(), helit->direction);
}

#pragma endregion

#pragma region Explode
HelitExlodedState::HelitExlodedState()
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

HelitExlodedState::~HelitExlodedState()
{
	delete sprite_;
}

void HelitExlodedState::Update()
{
	static Helit* helit;
	static Vec2 vel;
	helit = static_cast<Helit*>(this->owner);

	helit->body->SetLinearVelocity(Vec2{ 0, 0 });
}

void HelitExlodedState::Draw()
{
	static uint8 index = 0;
	static float32 f = 0.0f;
	static Helit* helit;

	helit = static_cast<Helit*>(this->owner);
	if (f < Debug::total_time)
	{
		index++;
		f = Debug::total_time + Debug::delta_time * delay_;

		if (index == 6)
			index = 0;
	}

	sprite_->Draw(index, helit->GetPosition(), helit->direction);
	// Debug::Log("%d\n", index + offset);
}
#pragma endregion
