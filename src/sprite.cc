#include "sprite.h"
#include <exception>
#include <cstdio>
#include "input.h"
#include "camera.h"
#include "window.h"

static D3DXMATRIX transform;
static AZORcamera g_camera;
static AZORwindow g_window;

Sprite::Sprite(const char* texture_alias)
	: texture_(nullptr), handler(nullptr), rects_(nullptr)
{
	this->texture_ = azorGetTexture(texture_alias);
	this->handler = azorGetRenderer()->handler;
}

Sprite::Sprite(const char* texture_alias, AZORrect rects)
	: texture_(nullptr), handler(nullptr), rects_(nullptr)
{
	this->texture_ = azorGetTexture(texture_alias);
	this->handler = azorGetRenderer()->handler;
	this->rects_ = rects;

	g_camera = azorGetCamera();
	g_window = azorGetWindow();
}

void Sprite::Draw(Vec2 position, uint64 color) const
{
	static D3DXVECTOR3 pos = D3DXVECTOR3{ 0, 0, 0 };
	static D3DXVECTOR2 translate = D3DXVECTOR2{ 0, 0 };

	assert(texture_ && handler);

	pos.x = position.x;
	pos.y = position.y;

	translate.x = g_window->width * 0.5f - g_camera->pos.x;
	translate.y = g_window->height * 0.5f - g_camera->pos.y;


	D3DXMatrixTransformation2D(
		&transform,
		nullptr,
		0.0f,
		nullptr,
		nullptr,
		D3DXToRadian(0),
		&translate);

	D3DXMATRIX oldMatrix;
	handler->GetTransform(&oldMatrix);
	handler->SetTransform(&transform);

	handler->SetTransform(&transform);
	handler->Draw(texture_->data, nullptr, nullptr, &pos, color);

	handler->GetTransform(&oldMatrix);
}

void Sprite::Draw(uint8 index, Vec2 position, int8 direction, uint64 color) const
{
	static D3DXVECTOR3 pos = D3DXVECTOR3{ 0, 0, 0 };
	static D3DXVECTOR3 center = D3DXVECTOR3{ 0,0,0 };

	static D3DXVECTOR2 sprite_center2 = D3DXVECTOR2{ 0,0};
	static D3DXVECTOR2 translate = D3DXVECTOR2{ 0, 0 };
	static D3DXVECTOR2 scale = D3DXVECTOR2{ 0, 1 };

	static RECT r = RECT{0, 0, 0, 0};
	assert(texture_ && handler && rects_);

	pos.x = position.x;
	pos.y = position.y;

	sprite_center2.x = position.x;
	sprite_center2.y = position.y;

	scale.x = direction;

	translate.x = g_window->width * 0.5f - g_camera->pos.x;
	translate.y = g_window->height * 0.5f - g_camera->pos.y;

	try
	{
		r.left = rects_[index].left;
		r.top = rects_[index].top;
		r.right = rects_[index].right;
		r.bottom = rects_[index].bottom;

		center.x = (rects_[index].right - rects_[index].left) * 0.5f;
		center.y = (rects_[index].bottom - rects_[index].top) * 0.5f;
	}
	catch (std::exception& e)
	{
		printf("SPRITE::ERROR::%s\n", e.what());
		return;
	}

	// sprite_center3.x = center.x;
	// sprite_center3.y = center.y;

	D3DXMatrixTransformation2D(
		&transform,
		&sprite_center2,
		0.0f,
		&scale,
		nullptr,
		D3DXToRadian(0),
		&translate);

	D3DXMATRIX oldMatrix;
	handler->GetTransform(&oldMatrix);
	handler->SetTransform(&transform);

	
	handler->Draw(texture_->data, &r, &center, &pos, color);
	

	handler->GetTransform(&oldMatrix);
}
