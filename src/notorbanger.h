#ifndef NOTORBANGER_H
#define NOTORBANGER_H

#include "object.h"

class Notorbanger : public Object
{
public:
	Notorbanger();
	~Notorbanger();

	void Start() override;
	void Update() override;
	void Draw() override;
	void OnColliderEnter(Object* collider) override;
	void OnColliderExit(Object* collider) override;
	Rect& GetBound() override;
};

#endif // NOTORBANGER_H
