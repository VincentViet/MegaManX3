#ifndef NOTORBANGER_STATES_H
#define NOTORBANGER_STATES_H

#include "../state.h"

class NotorbangerIdleState : public State
{
public:
	NotorbangerIdleState();
	~NotorbangerIdleState();

	void Update() override;
	void Draw() override;
};

class NotorbangerJumpState : public State
{
public:
	NotorbangerJumpState();
	~NotorbangerJumpState();

	void Update() override;
	void Draw() override;
};

class NotorbangerShootState : public State
{
public:
	NotorbangerShootState();
	~NotorbangerShootState();

	void Update() override;
	void Draw() override;
};

class NotorbangerExplodeState : public State
{
public:
	NotorbangerExplodeState();
	~NotorbangerExplodeState();

	void Update() override;
	void Draw() override;
};

#endif // NOTORBANGER_STATES_H