#ifndef SMALL_BUSTER_H
#define SMALL_BUSTER_H

#include "../bullet.h"

class SmallBuster : public Bullet
{
public:
	SmallBuster();
	~SmallBuster() = default;
protected:

	void Update() override;
	void Draw() override;

	Rect& GetBound() override;
private:
};

#endif // SMALL_BUSTER_H

