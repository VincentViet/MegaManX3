#ifndef HEADGUNNER_H
#define HEADGUNNER_H

#include "object.h"

class Headgunner : public Object
{
public:
	Headgunner();
	~Headgunner();

	void Start() override;
	void Update() override;
	void Draw() override;
	void OnColliderEnter(Object* collider) override;
	void OnColliderExit(Object* collider) override;
	Rect& GetBound() override;
};

#endif // HEADGUNNER_H
