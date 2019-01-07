#ifndef STATE_H
#define STATE_H
#include <common/settings.h>
#include "sprite.h"

#pragma region MegamanState
class State;
class MegamanIdle;
class MegamanRun;
#pragma endregion

class State
{
public:
	virtual ~State() = default;
	virtual void Update() = 0;
	virtual void Draw() = 0;

#pragma region MegamanState
	static MegamanIdle* megaman_idle;
	static MegamanRun*  megaman_run;
#pragma endregion

	// object binding;
	void* owner = nullptr;
protected:
	AZORsprite sprite_ = nullptr;
	int8 delay_ = 0;
private:
};

#endif // STATE_H

