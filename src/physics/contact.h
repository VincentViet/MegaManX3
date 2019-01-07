#ifndef CONTACT_H
#define CONTACT_H

#include "rigidbody.h"

struct ContactData
{
	bool IsCollided{};
	Rigidbody* first{};
	Rigidbody* second{};
	Vec2 normal;
};

#endif // CONTACT_H

