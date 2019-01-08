#ifndef HELIT_H
#define HELIT_H

#include "object.h"

class Helit : public Object
{
public:
	Helit();
	~Helit();

	void Start() override;
	void Update() override;
	void Draw() override;
	void OnColliderEnter(Object* collider) override;
	void OnColliderExit(Object* collider) override;
	Rect& GetBound() override;
};

#endif // HELIT_H
