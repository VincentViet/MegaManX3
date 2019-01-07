#ifndef RENDER_H
#define RENDER_H

#include <common/settings.h>
#include <dx9/d3d9.h>
#include <dx9/d3dx9.h>

typedef struct Renderer
{
	void Clear(uint64 color) const;
	void Begin() const;
	void End() const;
	void Reset();
	HRESULT Present() const;

	D3DPRESENT_PARAMETERS d3dpp;
	LPDIRECT3DDEVICE9 device9;
	LPD3DXSPRITE handler;
} Renderer, *AZORrenderer;

#ifdef __cplusplus
extern "C"
{
#endif
// int64		azorResetBackBuffer(const uint32 width, const uint32 height);
// void			azorResetRenderer();
void			azorDestroyRenderer(void);
AZORrenderer	azorGetRenderer();
#ifdef __cplusplus
}
#endif
#endif // RENDER_H