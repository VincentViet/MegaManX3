#include "megaman_states.h"
#include "../input.h"
#include "../megaman.h"
#include "../debug.h"
#include "../camera.h"
#include <vector>

MegamanIdle* State::megaman_idle;
MegamanRun*	State::megaman_run;

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

	megaman = static_cast<Megaman*>(this->owner);
	if (azorIsKeyDown(Keys::LEFTARROW))
	{
		megaman->direction = -1;
		megaman->ChangeState(State::megaman_run);
	}
	else if (azorIsKeyDown(Keys::RIGHTARROW))
	{
		megaman->direction = 1;
		megaman->ChangeState(State::megaman_run);
	}
}

void MegamanIdle::Draw()
{
	static uint8 index = 0;
	static float32 f = 0.0f;
	static Megaman* megaman;
	static AZORcamera g_camera;

	g_camera = azorGetCamera();
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
	};

	delay_ = 5;
	sprite_ = new Sprite(MEGAMAN_ALIAS, rects.data());
}

MegamanRun::~MegamanRun()
{
	delete sprite_;
}

void MegamanRun::Update()
{
	static Megaman* megaman;

	megaman = static_cast<Megaman*>(this->owner);
	if (azorIsKeyDown(Keys::LEFTARROW))
	{
		megaman->vel.x = -50;
	}
	else if (azorIsKeyDown(Keys::RIGHTARROW))
	{
		megaman->vel.x = 50;
	}
	else
	{
		megaman->vel.x = 0;
		megaman->ChangeState(State::megaman_idle);
	}
}

void MegamanRun::Draw()
{
	static uint8 index = 0;
	static float32 f = 0.0f;
	static Megaman* megaman;
	static AZORcamera g_camera;

	g_camera = azorGetCamera();
	megaman = static_cast<Megaman*>(this->owner);
	if (f < Debug::total_time)
	{
		index++;
		f = Debug::total_time + Debug::delta_time * delay_;

		if (index == 11)
			index = 0;
	}

	sprite_->Draw(index, megaman->GetPosition(), megaman->direction);
}
#pragma endregion

