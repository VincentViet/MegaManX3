#ifndef GENJI_H
#define GENJI_H

#include "object.h"

class Genji : public Object
{
public:
	Genji();
	~Genji();

	void Start() override;
	void Update() override;
	void Draw() override;
	void OnColliderEnter(Object* collider) override;
	void OnColliderExit(Object* collider) override;
	Rect& GetBound() override;
};

#endif // GENJI_H
