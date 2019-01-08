#ifndef BLASTHORNET_STATES_H
#define BLASTHORNET_STATES_H

#include "../state.h"

class BlasthornetIdleState : public State
{
public:
	BlasthornetIdleState();
	~BlasthornetIdleState();

	void Update() override;
	void Draw() override;
};

class BlasthornetStingState : public State
{
public:
	BlasthornetStingState();
	~BlasthornetStingState();

	void Update() override;
	void Draw() override;
};

class BlasthornetCallState : public State
{
public:
	BlasthornetCallState();
	~BlasthornetCallState();

	void Update() override;
	void Draw() override;
};

class BlasthornetExplodeState : public State
{
public:
	BlasthornetExplodeState();
	~BlasthornetExplodeState();

	void Update() override;
	void Draw() override;
};

#endif // BLASTHORNET_STATES_H