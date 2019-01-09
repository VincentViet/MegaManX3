#ifndef OBJECT_H
#define OBJECT_H

#include <common/math.h>
#include "physics.h"
#include "state.h"

typedef class Object
{
public:
	Object();
	explicit Object(Tag tag);
	
	virtual void Start() {}
	virtual void Update();
	virtual void Draw() {}
	
	virtual void OnColliderEnter(Object* collider) {}
	virtual void OnColliderExit(Object* collider) {}
	void ChangeState(State* state);
	virtual Rect& GetBound(); 

	Vec2 GetPosition() const;

	virtual ~Object();

	Tag tag;
	Rigidbody* body{};
	int8 direction = 1;
	bool is_jumping = true;
	bool is_touch_elevator = false;
	BodyDecs body_decs;
	ColliderDecs collider_decs;
	int32 id{};
	Vec2 position;
	State* state{};

protected:
} Object, *AZORobject;

#endif // OBJECT_H
