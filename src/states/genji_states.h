#ifndef GENJI_STATES_H
#define GENJI_STATES_H

#include "../state.h"

class GenjiIdleState : public State
{
public:
	GenjiIdleState();
	~GenjiIdleState();

	void Update() override;
	void Draw() override;
};

class GenjiRotateState : public State
{
public:
	GenjiRotateState();
	~GenjiRotateState();

	void Update() override;
	void Draw() override;
};

class GenjiExplodeState : public State
{
public:
	GenjiExplodeState();
	~GenjiExplodeState();

	void Update() override;
	void Draw() override;
};

#endif // GENJI_STATES_H