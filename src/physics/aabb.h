#ifndef AABB_H
#define AABB_H

#include <common/math.h>

typedef struct AABB
{
	float32 x;
	float32 y;
	float32 width;
	float32 height;
} AABB, *AZORaabb;

#endif // AABB_H
