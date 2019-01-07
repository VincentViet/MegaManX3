#ifndef MEGAMAN_STATES_H
#define MEGAMAN_STATES_H

#include "../state.h"

class MegamanIdle : public State
{
public:
	MegamanIdle();
	~MegamanIdle();

	void Update() override;
	void Draw() override;
};

class MegamanRun : public State
{
public:
	MegamanRun();
	~MegamanRun();

	void Update() override;
	void Draw() override;
};

#endif // MEGAMAN_STATES_H

