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

	static float f = 1.0f;
	if (f < 0.0f)
	{
		genji->ChangeState(State::genji_rotate);
		f = 1.0f;
	}
	else
	{
		f -= Debug::delta_time;
	}
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
		{3, 412, 3 + 46, 412 + 50},
		{54, 412, 54 + 45, 412 + 50},
		{103, 412, 103 + 45, 412 + 50},
		{150, 412, 150 + 41, 412 + 50},
		{198, 412, 198 + 36, 412 + 50},
		{238, 412, 238 + 36, 412 + 50},
		{278, 412, 278 + 36, 412 + 48},
		{315, 412, 315 + 31, 412 + 50},
		{348, 412, 348 + 36, 412 + 50},
		{412, 412, 412 + 24, 412 + 50},
		{440, 412, 440 + 21, 412 + 50},
		{465, 412, 465 + 14, 412 + 50},
		{486, 412, 486 + 10, 412 + 50},
		{503, 412, 503 + 9, 412 + 50},
		{517, 412, 517 + 9, 412 + 50},
		{530, 412, 530 + 9, 412 + 50},

		{517, 412, 517 + 9, 412 + 50},
		{503, 412, 503 + 9, 412 + 50},
		{486, 412, 486 + 10, 412 + 50},
		{465, 412, 465 + 14, 412 + 50},
		{440, 412, 440 + 21, 412 + 50},
		{412, 412, 412 + 24, 412 + 50},
		{348, 412, 348 + 36, 412 + 50},
		{315, 412, 315 + 31, 412 + 50},
		{278, 412, 278 + 36, 412 + 48},
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

	static float f = 5.0f;
	if (f < 0.0f)
	{
		genji->ChangeState(State::genji_idle);
		f = 5.0f;
	}
	else
	{
		f -= Debug::delta_time;
	}
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

		if (index == 25)
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
