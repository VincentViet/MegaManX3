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

private:
	// bool is_shooting;
};

class MegamanJump : public State
{
public:
	MegamanJump();
	~MegamanJump();

	void Update() override;
	void Draw() override;

private:
	// bool is_shooting;
};

class MegamanShoot : public State
{
public:
	MegamanShoot();
	~MegamanShoot();

	void Update() override;
	void Draw() override;
};

class MegamanDash : public State
{
public:
	MegamanDash();
	~MegamanDash();

	void Update() override;
	void Draw() override;

private:
	// bool is_shooting;
};

class MegamanClimb : public State
{
public:
	MegamanClimb();
	~MegamanClimb();

	void Update() override;
	void Draw() override;

private:
	// bool is_shooting;
};

#endif // MEGAMAN_STATES_H

