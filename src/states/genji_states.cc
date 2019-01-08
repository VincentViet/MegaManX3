#include "genji_states.h"
#include "../genji.h"
#include "../debug.h"
#include <vector>

GenjiIdleState*		State::genji_idle;
GenjiRotateState*	State::genji_rotate;
GenjiExplodeState*	State::genji_exploded;

#pragma region Idle
GenjiIdleState::GenjiIdleState()
{
	static std::vector<Rect> rects
	{
		{328, 10, 375, 59} };

	delay_ = 5;

	sprite_ = new Sprite(GENJI_ALIAS, rects.data());
}

GenjiIdleState::~GenjiIdleState()
{
	delete sprite_;
}

void GenjiIdleState::Update()
{
	static Genji* genji;
	genji = static_cast<Genji*>(this->owner);
	genji->body->SetLinearVelocity(Vec2{ 0, 0 });
}

void GenjiIdleState::Draw()
{
	static uint8 index = 0;
	static Genji* genji;
	genji = static_cast<Genji*>(this->owner);

	sprite_->Draw(index, genji->GetPosition(), genji->direction);
}
#pragma endregion

#pragma region Rotate
GenjiRotateState::GenjiRotateState()
{
	static std::vector<Rect> rects
	{
		{15, 271, 62, 318},
		{69, 271, 114, 316},
		{120, 273, 167, 320},
		{174, 271, 223, 320},
		{228, 271, 277, 320},
		{284, 274, 331, 321},
		{340, 274, 385, 319},
		{399, 274, 444, 319},
		{451, 273, 498, 320},
		{502, 274, 551, 323},
	};

	delay_ = 5;

	sprite_ = new Sprite(GENJI_ALIAS, rects.data());
}

GenjiRotateState::~GenjiRotateState()
{
	delete sprite_;
}

void GenjiRotateState::Update()
{
	static Genji* genji;
	genji = static_cast<Genji*>(this->owner);
	genji->body->SetLinearVelocity(Vec2{ 0, 0 });
}

void GenjiRotateState::Draw()
{
	static uint8 index = 0;
	static float32 f = 0.0f;
	static Genji* genji;

	genji = static_cast<Genji*>(this->owner);
	if (f < Debug::total_time)
	{
		index++;
		f = Debug::total_time + Debug::delta_time * delay_;

		if (index == 11)
			index = 0;
	}

	sprite_->Draw(index, genji->GetPosition(), genji->direction);
}
#pragma endregion

#pragma region Explode
GenjiExplodeState::GenjiExplodeState()
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

GenjiExplodeState::~GenjiExplodeState()
{
	delete sprite_;
}

void GenjiExplodeState::Update()
{
	static Genji* genji;
	genji = static_cast<Genji*>(this->owner);
	genji->body->SetLinearVelocity(Vec2{ 0, 0 });
}

void GenjiExplodeState::Draw()
{
	static uint8 index = 0;
	static float32 f = 0.0f;
	static Genji* genji;

	genji = static_cast<Genji*>(this->owner);
	if (f < Debug::total_time)
	{
		index++;
		f = Debug::total_time + Debug::delta_time * delay_;

		if (index == 7)
			index = 0;
	}

	sprite_->Draw(index, genji->GetPosition(), genji->direction);
}
#pragma endregion
