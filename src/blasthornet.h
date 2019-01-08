#ifndef BLASTHORNET_H
#define BLASTHORNET_H

#include "object.h"

class Blasthornet : public Object
{
public:
	Blasthornet();
	~Blasthornet();

	void Start() override;
	void Update() override;
	void Draw() override;
	void OnColliderEnter(Object* collider) override;
	void OnColliderExit(Object* collider) override;
	Rect& GetBound() override;
};

#endif // BLASTHORNET_H
