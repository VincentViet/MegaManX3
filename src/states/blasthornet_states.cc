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

	static float f = 2.0f;
	if (f < 0.0f)
	{
		blasthornet->ChangeState(State::blasthornet_sting);
		f = 2.0f;
	}
	else
	{
		f -= Debug::delta_time;
	}
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
		{16, 189, 63, 266},//dong3
		{69, 192, 143, 266},
		{148, 210, 244, 266},
		{248, 190, 295, 266},
		{298, 189, 373, 266},
		{376, 208, 472, 266},

		{15, 275, 62, 352},//dong4
		{67, 276, 141, 352},
		{146, 294, 240, 352},
		{248, 275, 295, 355},
		{299, 276, 373, 355},
		{377, 294, 473, 355},

		{15, 358, 62, 438},//dong5
		{66, 359, 140, 438},
		{145, 377, 241, 438},
		{250,358 , 297, 438},
		{302, 359, 376, 438},
		{382, 377, 478, 438},

		{14, 446, 62, 527},//dong6
		{70, 447, 144, 527},
		{149, 465, 245, 527},
		{251, 446, 300, 526},
		{306, 447, 380, 526},
		{386, 465, 482, 526},

		{16, 537, 63, 617},//dong7
		{69, 538, 148, 617},
		{155, 556, 251, 617},
		{260, 537, 308, 617},
		{315, 538, 389, 617},
		{394, 556, 490, 617},
	};

	delay_ = 10;

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

	static float f = 4.0f;
	if (f < 0.0f)
	{
		blasthornet->ChangeState(State::blasthornet_call);
		f = 4.0f;
	}
	else
	{
		f -= Debug::delta_time;
	}
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

		if (index == 30)
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
		{15, 99, 62, 183},//dong2
		{67, 99, 141, 183},
		{144, 117, 240, 183},
		{247, 99, 294, 180},
		{299, 100, 373, 180},
		{377, 118, 472, 180},
	};

	delay_ = 10;

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

	static float f = 2.0f;
	if (f < 0.0f)
	{
		blasthornet->ChangeState(State::blasthornet_idle);
		f = 2.0f;
	}
	else
	{
		f -= Debug::delta_time;
	}
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

		if (index == 4)
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
