#ifndef STATE_H
#define STATE_H
#include <common/settings.h>
#include "sprite.h"

#pragma region MegamanState
class State;
class MegamanIdle;
class MegamanRun;
class MegamanJump;
class MegamanShoot;
class MegamanDash;
class MegamanClimb;
#pragma endregion

#pragma region HelitState

class HelitIdleState;
class HelitExlodedState;
class BulletHelitIdleState;
class BulletHelitExplodeState;
#pragma endregion

#pragma region NotorbangerState
class NotorbangerIdleState;
class NotorbangerJumpState;
class NotorbangerShootState;
class NotorbangerExplodeState;
class CandyBulletIdleState;
class CandyBulletExplodeState;
#pragma endregion

#pragma region Headgunner
class HeadgunnerIdleState;
class HeadgunnerShootState;
class HeadgunnerExplodeState;
class BulletHeadgunnerIdleState;
class BulletHeadgunnerExplodeState;
#pragma endregion

#pragma region Genji
class GenjiIdleState;
class GenjiRotateState;
class GenjiExplodeState;
#pragma endregion

#pragma region Blasthornet
class BlasthornetIdleState;
class BlasthornetStingState;
class BlasthornetCallState;
class BlasthornetExplodeState;
#pragma endregion

class State
{
public:
	virtual ~State() = default;
	virtual void Update() = 0;
	virtual void Draw() = 0;

#pragma region MegamanState
	static MegamanIdle*		megaman_idle;
	static MegamanRun*		megaman_run;
	static MegamanJump*		megaman_jump;
	static MegamanShoot*	megaman_shoot;
	static MegamanDash*		megaman_dash;
	static MegamanClimb*	megaman_climb;
#pragma endregion

#pragma region HelitState
	static HelitIdleState*				helit_idle;
	static HelitExlodedState*			helit_exploded;
	static BulletHelitIdleState*		bullet_helit_idle;
	static BulletHelitExplodeState*		bullet_helit_exploded;
#pragma endregion

#pragma region NotorbangerState
	static NotorbangerIdleState*			notorbanger_idle;
	static NotorbangerJumpState*			notorbanger_jump;
	static NotorbangerShootState*			notorbanger_shoot;
	static NotorbangerExplodeState*			notorbanger_exploded;
	static CandyBulletIdleState*			candy_bullet_idle;
	static CandyBulletExplodeState*			candy_bullet_exploded;
#pragma endregion

#pragma region HeadgunnerState
	static HeadgunnerIdleState*				headgunner_idle;
	static HeadgunnerShootState*			headgunner_shoot;
	static HeadgunnerExplodeState*			headgunner_exploded;
	static BulletHeadgunnerIdleState*		bullet_headgunner_idle;
	static BulletHeadgunnerExplodeState*	bullet_headgunner_exploded;
#pragma endregion

#pragma region Genji
	static GenjiIdleState*				genji_idle;
	static GenjiRotateState*			genji_rotate;
	static GenjiExplodeState*			genji_exploded;
#pragma endregion

#pragma region BlastHornetState
	static BlasthornetIdleState*		blasthornet_idle;
	static BlasthornetStingState*		blasthornet_sting;
	static BlasthornetCallState*		blasthornet_call;
	static BlasthornetExplodeState*		blasthornet_exploded;
#pragma endregion

	// object binding;
	void* owner = nullptr;
protected:
	AZORsprite sprite_ = nullptr;
	int8 delay_ = 0;
private:
};

#endif // STATE_H

