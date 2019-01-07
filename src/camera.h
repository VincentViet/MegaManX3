#ifndef CAMERA_H
#define CAMERA_H

#include "object.h"

typedef class Camera
{
public:
	explicit Camera(int32 width, int32 height, Vec2 pos);
	~Camera() = default;

	void Update();
	void Follow(Object* target);
	bool IsContained(Object* target) const;

	Vec2 GetPosition() const;

	int32 width;
	int32 height;
	Rect bound{};
	Vec2 pos;
	bool is_follwing_x;
	bool is_follwing_y;
protected:
private:
	Object* target_;
} Camera, *AZORcamera;

AZORcamera	azorGetCamera(void);
void		azorDestroyCamera(void);

#endif // CAMERA_H
