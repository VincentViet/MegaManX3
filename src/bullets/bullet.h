#ifndef BULLET_H
#define BULLET_H

#include "../object.h"

class Bullet : public Object
{
public:
	Bullet();
	~Bullet();

	void SetActive(bool active) const;
protected:
	AZORsprite sprite_{};
};

#endif // BULLET_H

