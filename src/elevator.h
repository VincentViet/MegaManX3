<<<<<<< HEAD
=======
#ifndef ELEVATOR_H
#define ELEVATOR_H

#include "object.h"

class Elevator : public Object
{
public:
	Elevator();
	~Elevator();

	void Start() override;
	void Update() override;
	void Draw() override;
	void OnColliderEnter(Object* collider) override;
	void OnColliderExit(Object* collider) override;

private:
	bool is_active;
	Sprite* sprite_;
};

#endif // ELEVATOR_H

>>>>>>> VincentViet
