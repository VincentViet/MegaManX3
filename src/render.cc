#include "render.h"
#include "window.h"
#include "debug.h"

static AZORrenderer g_renderer;

Renderer* azorGetRenderer()
{
	if (!g_renderer)
	{
		const auto window = azorGetWindow();
		if (!window)
			return nullptr;

		LPDIRECT3D9 d3d9;
		if ((d3d9 = Direct3DCreate9(D3D_SDK_VERSION)) == nullptr)
		{
			azorDestroyWindow();
			return nullptr;
		}

		g_renderer = new Renderer;
		memset(g_renderer, 0, sizeof(Renderer));

		ZeroMemory(&g_renderer->d3dpp, sizeof D3DPRESENT_PARAMETERS);
		g_renderer->d3dpp.Windowed = TRUE;
		g_renderer->d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		g_renderer->d3dpp.hDeviceWindow = window->handler;
		g_renderer->d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;

		if (d3d9->CreateDevice(
			D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			window->handler,
			D3DCREATE_HARDWARE_VERTEXPROCESSING,
			&g_renderer->d3dpp,
			reinterpret_cast<IDirect3DDevice9**>(&g_renderer->device9)) < 0)
		{
			azorDestroyWindow();

			delete g_renderer;
			g_renderer = nullptr;
		}

		d3d9->Release();

		D3DXCreateSprite(g_renderer->device9, &g_renderer->handler);
	}

	return g_renderer;
}

void Renderer::Clear(const uint64 color) const
{
	device9->Clear(0, nullptr, D3DCLEAR_TARGET, color, 1.0f, 0);
}

void Renderer::Begin() const
{
	device9->BeginScene();
	handler->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_DO_NOT_ADDREF_TEXTURE);
}

void Renderer::End() const
{
	handler->End();
	azorRenderDebug();
	device9->EndScene();
}

void Renderer::Reset()
{
	device9->Reset(&d3dpp);
}

HRESULT Renderer::Present() const
{
	return device9->Present(nullptr, nullptr, nullptr, nullptr);
}

void azorDestroyRenderer()
{
	g_renderer->handler->Release();
	g_renderer->device9->Release();
	delete g_renderer;
	g_renderer = nullptr;
}
