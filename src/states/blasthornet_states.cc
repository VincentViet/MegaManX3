#include "blasthornet_states.h"
#include "../blasthornet.h"
#include "../debug.h"
#include <vector>

BlasthornetIdleState*		State::blasthornet_idle;
BlasthornetStingState*		State::blasthornet_sting;
BlasthornetCallState*		State::blasthornet_call;
BlasthornetExplodeState*	State::blasthornet_exploded;

#pragma region Idle
BlasthornetIdleState::BlasthornetIdleState()
{
	static std::vector<Rect> rects
	{
		{66, 3, 116, 93},
		{122, 4, 196, 93},
		{200, 21, 296, 93},
		{302, 22, 398, 93},
	};

	delay_ = 5;

	sprite_ = new Sprite(BLASTHORNET_ALIAS, rects.data());
}

BlasthornetIdleState::~BlasthornetIdleState()
{
	delete sprite_;
}

void BlasthornetIdleState::Update()
{
	static Blasthornet* blasthornet;
	blasthornet = static_cast<Blasthornet*>(this->owner);
	blasthornet->body->SetLinearVelocity(Vec2{ 0, 0 });
}

void BlasthornetIdleState::Draw()
{
	static uint8 index = 0;
	static float32 f = 0.0f;
	static Blasthornet* blasthornet;

	blasthornet = static_cast<Blasthornet*>(this->owner);
	if (f < Debug::total_time)
	{
		index++;
		f = Debug::total_time + Debug::delta_time * delay_;

		if (index == 4)
			index = 0;
	}

	sprite_->Draw(index, blasthornet->GetPosition(), blasthornet->direction);
}
#pragma endregion

#pragma region Sting
BlasthornetStingState::BlasthornetStingState()
{
	static std::vector<Rect> rects
	{
		{66, 3, 116, 93},
		{122, 4, 196, 93},
		{200, 21, 296, 93},
		{302, 22, 398, 93},
	};

	delay_ = 5;

	sprite_ = new Sprite(BLASTHORNET_ALIAS, rects.data());
}

BlasthornetStingState::~BlasthornetStingState()
{
	delete sprite_;
}

void BlasthornetStingState::Update()
{
	static Blasthornet* blasthornet;
	blasthornet = static_cast<Blasthornet*>(this->owner);
	blasthornet->body->SetLinearVelocity(Vec2{ 0, 0 });
}

void BlasthornetStingState::Draw()
{
	static uint8 index = 0;
	static float32 f = 0.0f;
	static Blasthornet* blasthornet;

	blasthornet = static_cast<Blasthornet*>(this->owner);
	if (f < Debug::total_time)
	{
		index++;
		f = Debug::total_time + Debug::delta_time * delay_;

		if (index == 5)
			index = 0;
	}

	sprite_->Draw(index, blasthornet->GetPosition(), blasthornet->direction);
}
#pragma endregion

#pragma region Call
BlasthornetCallState::BlasthornetCallState()
{
	static std::vector<Rect> rects
	{
		{66, 3, 116, 93},
		{122, 4, 196, 93},
		{200, 21, 296, 93},
		{302, 22, 398, 93},
	};

	delay_ = 5;

	sprite_ = new Sprite(BLASTHORNET_ALIAS, rects.data());
}

BlasthornetCallState::~BlasthornetCallState()
{
	delete sprite_;
}

void BlasthornetCallState::Update()
{
	static Blasthornet* blasthornet;
	blasthornet = static_cast<Blasthornet*>(this->owner);
	blasthornet->body->SetLinearVelocity(Vec2{ 0, 0 });
}

void BlasthornetCallState::Draw()
{
	static uint8 index = 0;
	static float32 f = 0.0f;
	static Blasthornet* blasthornet;

	blasthornet = static_cast<Blasthornet*>(this->owner);
	if (f < Debug::total_time)
	{
		index++;
		f = Debug::total_time + Debug::delta_time * delay_;

		if (index == 5)
			index = 0;
	}

	sprite_->Draw(index, blasthornet->GetPosition(), blasthornet->direction);
}
#pragma endregion

#pragma region Explode
BlasthornetExplodeState::BlasthornetExplodeState()
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

BlasthornetExplodeState::~BlasthornetExplodeState()
{
	delete sprite_;
}

void BlasthornetExplodeState::Update()
{
	static Blasthornet* blasthornet;
	blasthornet = static_cast<Blasthornet*>(this->owner);
	blasthornet->body->SetLinearVelocity(Vec2{ 0, 0 });
}


void BlasthornetExplodeState::Draw()
{
	static uint8 index = 0;
	static float32 f = 0.0f;
	static Blasthornet* blasthornet;

	blasthornet = static_cast<Blasthornet*>(this->owner);
	if (f < Debug::total_time)
	{
		index++;
		f = Debug::total_time + Debug::delta_time * delay_;

		if (index == 5)
			index = 0;
	}

	sprite_->Draw(index, blasthornet->GetPosition(), blasthornet->direction);
}
#pragma endregion
