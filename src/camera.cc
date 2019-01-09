#include "camera.h"
#include "render.h"
#include "window.h"
#include "debug.h"

static AZORcamera g_camera;
// static bool is_follwing_x;
// static bool is_follwing_y;

Camera::Camera(int32 width, int32 height, Vec2 pos)
	: width(width), height(height), pos(pos), target_(nullptr)
{
	bound.left = pos.x - width * 0.5f;
	bound.right = pos.x + width * 0.5f;
	bound.top = pos.y - height * 0.5f;
	bound.bottom = pos.y + height * 0.5f;

	is_follwing_x = true;
	is_follwing_y = true;
	offset_x = offset_y = 0;
}

void Camera::Update()
{
	if (target_)
	{
		if (is_follwing_x)
		{
			if (bound.left < 0)
			{
				pos.x = /*width * 0.5f*/ 400;
				is_follwing_x = false;
			}
			else if (bound.right > MAP_MAX_WIDTH)
			{
				pos.x = MAP_MAX_WIDTH - 400 /*width * 0.5f*/;
				is_follwing_x = false;
			}
			else
			{
				// pos.x = target_->body->GetPosition().x + bound.left;
				// if (offset_x != 0.0f)
				// {
				// 	pos.x += offset_x + 0.5f * offset_x / b2Abs(offset_x);
				// }
				// pos.x = offset_x;
				if (target_->is_touch_elevator)
				{
					pos.x += offset_x;
				}
				else { pos.x = target_->position.x; }
			}
		}
		else
		{
			if (target_->body->GetPosition().x >= width * 0.5f && bound.right < MAP_MAX_WIDTH)
				is_follwing_x = true;
		}
		
		if (is_follwing_y)
		{
			if (bound.top < 0)
			{
				pos.y = height * 0.5f;
				is_follwing_y = false;
			}
			else if (bound.bottom > MAP_MAX_HEIGHT)
			{
				pos.y = MAP_MAX_HEIGHT - height * 0.5f;
				is_follwing_y = false;
				return;
			}
			else
			{
				
				// if (offset_y != 0.0f)
				// {
				// 	pos.y += offset_y + 0.5f * offset_y / b2Abs(offset_y);
				// }
				if (target_->is_touch_elevator)
				{
					pos.y += offset_y;
				}
				else
				{
					pos.y = target_->position.y;
				}
			}

		}
		else
		{
			if (target_->body->GetPosition().y <= height * 0.5f)
				is_follwing_y = true;
		}

		// if (is_follwing_x)
		// {
		// 	if (bound.left < 0)
		// 	{
		// 		pos.x = /*width * 0.5f*/ 400;
		// 		is_follwing_x = false;
		// 	}
		// 	else if (bound.right > MAP_MAX_WIDTH)
		// 	{
		// 		pos.x = MAP_MAX_WIDTH - 400 /*width * 0.5f*/;
		// 		is_follwing_x = false;
		// 	}
		// 	else
		// 	{
		// 		pos.x = target_->position.x;
		// 	}
		// }
		// else
		// {
		// 	if (target_->position.x >= this->pos.x)
		// 		is_follwing_x = true;
		// }
		//
		// if (is_follwing_y)
		// {
		// 	if (bound.top < 0)
		// 	{
		// 		pos.y = height * 0.5f;
		// 		is_follwing_y = false;
		// 	}
		// 	else if (bound.bottom > MAP_MAX_HEIGHT)
		// 	{
		// 		pos.y = MAP_MAX_HEIGHT - height * 0.5f;
		// 		is_follwing_y = false;
		// 		return;
		// 	}
		// 	else
		// 	{
		// 		pos.y = target_->position.y;
		// 	}
		// }
		// else
		// {
		// 	if (target_->position.y <= this->pos.y)
		// 		is_follwing_y = true;
		// }

		Debug::Log("x: %d, y: %d\n", bound.left, bound.top);
	}

	bound.left = pos.x - width * 0.5f;
	bound.right = pos.x + width * 0.5f;
	bound.top = pos.y - height * 0.5f;
	bound.bottom = pos.y + height * 0.5f;
}

void Camera::Follow(Object* target)
{
	target_ = target;
}

bool Camera::IsContained(Object* target) const
{
	static Rect bound;
	
	bound = target->GetBound();
	return !(this->bound.left > bound.right ||
		this->bound.right < bound.left ||
		this->bound.top > bound.bottom ||
		this->bound.bottom < bound.top);
}

Vec2 Camera::GetPosition() const
{
	return this->pos;
}

AZORcamera azorGetCamera()
{
	if (!g_camera)
	{
		const auto width = azorGetWindow()->width;
		const auto height = azorGetWindow()->height;
		g_camera = 
			new Camera(width, height, Vec2{width * 0.5f, height * 0.5f});
	}

	return g_camera;
}

void azorDestroyCamera()
{
	delete g_camera;
}
