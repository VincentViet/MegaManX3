#ifndef SPRITE_H
#define SPRITE_H

#include <dx9/d3dx9.h>
#include "resources.h"
#include <common/math.h>

typedef class Sprite
{
public:
	explicit Sprite(const char* texture_alias);
	explicit Sprite(const char* texture_alias, AZORrect rects);
	~Sprite() = default;

	void Draw(Vec2 position, uint64 color = COLOR_RGB(255, 255, 255)) const;
	void Draw(uint8 index, Vec2 position, int8 direction, uint64 color = COLOR_RGB(255, 255, 255)) const;

protected:
	AZORTexture texture_;
	LPD3DXSPRITE handler;
	AZORrect rects_;

private:
} Sprite, *AZORsprite;

#endif // SPRITE_H

