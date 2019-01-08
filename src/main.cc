#include <common/math.h>
#include <imgui/imgui_impl_dx9.h>
#include "window.h"
#include "render.h"
#include "input.h"
#include "sprite.h"
#include "camera.h"
#include "debug.h"
#include "scenes.h"
#include "physics.h"


extern void LoadResources();
extern void InitializeMap();
extern void CleanUp();

static AZORrenderer g_renderer;
static AZORwindow	g_window;
static AZORscene	g_scene;
static AZORcamera	g_main_camera;
static AZORphysics	g_physics;

static AZORsprite g_background;

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT WINAPI WindProc(HWND hwnd, uint32 msg, WPARAM wparam, LPARAM lparam)
{
	if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam))
		return true;

	switch (msg)
	{
	case WM_KEYDOWN:
		if (wparam == VK_ESCAPE)
			DestroyWindow(hwnd);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_SIZE:
		if (g_renderer && wparam != SIZE_MINIMIZED)
		{
			ImGui_ImplDX9_InvalidateDeviceObjects();
			ImGui_ImplDX9_CreateDeviceObjects();
		}
		return 0;

	case WM_SYSCOMMAND:
		if ((wparam & 0xfff0) == SC_KEYMENU)
			return 0;
		break;

	default:
		break;
	}
	return DefWindowProc(hwnd, msg, wparam, lparam);
}


void GameStart()
{
	g_window = azorGetWindow();
	g_renderer = azorGetRenderer();

	if (!g_window || !g_renderer)
	{
		system("PAUSE");
		exit(0);
	}

	g_scene = azorGetScene();
	g_main_camera = azorGetCamera();
	g_physics = azorGetPhysics();

	LoadResources();

	g_background = new Sprite("bg");

	InitializeMap();
}

void GameRun()
{
	MSG msg;
	ZeroMemory(&msg, sizeof msg);

	const auto hwnd = azorGetWindow()->handler;

	g_window->Show();

	g_scene->Start();

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		//Game Loop
		azorPollInput(hwnd);

		g_main_camera->Update();
		g_physics->Update();
		g_scene->Update();

		g_renderer->Clear(Debug::clear_color);
		g_renderer->Begin();

		g_background->Draw(Vec2{0,0});
		g_scene->Draw();

		g_renderer->End();

		if (g_renderer->Present() &&
			g_renderer->device9->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
		{
			ImGui_ImplDX9_InvalidateDeviceObjects();
			g_renderer->Reset();
			ImGui_ImplDX9_CreateDeviceObjects();
		}
	}
	CleanUp();
}

void GameEnd()
{
	azorDestroyPhysics();
	azorDestroyInput();
	azorClearResources();
	azorDestroyRenderer();
	azorDestroyCamera();
	azorDestroyWindow();
	azorDestroyDebug();
}

int main(int argc, char* argv[])
{
	UNUSED_VAR(argc);
	UNUSED_VAR(argv);

	GameStart();
	GameRun();
	GameEnd();
}
