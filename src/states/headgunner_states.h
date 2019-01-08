#ifndef HEADGUNNER_STATES_H
#define HEADGUNNER_STATES_H

#include "../state.h"

class HeadgunnerIdleState : public State
{
public:
	HeadgunnerIdleState();
	~HeadgunnerIdleState();

	void Update() override;
	void Draw() override;
};

class HeadgunnerShootState : public State
{
public:
	HeadgunnerShootState();
	~HeadgunnerShootState();

	void Update() override;
	void Draw() override;
};

class HeadgunnerExplodeState : public State
{
public:
	HeadgunnerExplodeState();
	~HeadgunnerExplodeState();

	void Update() override;
	void Draw() override;
};

#endif // HEADGUNNER_STATES_H