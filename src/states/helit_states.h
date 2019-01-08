#ifndef HELIT_STATES_H
#define HELIT_STATES_H

#include "../state.h"

class HelitIdleState : public State
{
public:
	HelitIdleState();
	~HelitIdleState();

	void Update() override;
	void Draw() override;
};

class HelitExlodedState : public State
{
public:
	HelitExlodedState();
	~HelitExlodedState();

	void Update() override;
	void Draw() override;
};

#endif // HELIT_STATES_H