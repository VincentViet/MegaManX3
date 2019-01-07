#include "window.h"
#include <jansson/jansson.h>
#include <Windows.h>

static AZORwindow g_window = nullptr;
static WNDCLASSEX wcex;

extern LRESULT WINAPI WindProc(HWND hwnd, uint32 msg, WPARAM wparam, LPARAM lparam);

void Window::Show() const
{
	ShowWindow(handler, SW_SHOWDEFAULT);
	UpdateWindow(handler);
}

Window* azorGetWindow()
{
	if (!g_window)
	{
		json_error_t error;
		const auto configs = 
			static_cast<json_t*>(azorGetConfigsContent(&error));
		if (!configs)
		{
			printf(
				"Jansson Error: %s at line %d column %d\n",
				error.text,
				error.line,
				error.column);
			return nullptr;
		}

		g_window = new Window;
		memset(g_window, 0, sizeof(Window));

		const auto window_configs = json_object_get(configs, "Window");
		g_window->width = 
			json_integer_value(json_object_get(window_configs, "width"));
		g_window->height = 
			json_integer_value(json_object_get(window_configs, "height"));
		g_window->title =
			json_string_value(json_object_get(window_configs, "title"));

		//center window
		const auto screen_width = GetSystemMetrics(SM_CXSCREEN);
		const auto screen_height = GetSystemMetrics(SM_CYSCREEN);
		g_window->x = (screen_width - g_window->width) / 2;
		g_window->y = (screen_height - g_window->height) / 2;

		wcex = 
		{
			sizeof(WNDCLASSEX),
			CS_CLASSDC,
			WindProc,
			0L, 0L,
			GetModuleHandle(nullptr),
			nullptr, nullptr, nullptr, nullptr,
			g_window->title,
			nullptr
		};

		RegisterClassEx(&wcex);
		g_window->handler = CreateWindow(
			g_window->title,
			g_window->title,
			WS_OVERLAPPEDWINDOW,
			g_window->x,
			g_window->y,
			g_window->width,
			g_window->height,
			nullptr, nullptr,
			wcex.hInstance,
			nullptr
		);

		if (!g_window->handler)
		{
			UnregisterClass(g_window->title, wcex.hInstance);
			delete g_window;
			g_window = nullptr;
		}
	}

	return g_window;
}

void azorShowWindow()
{
	assert(g_window != nullptr);
	const auto hwnd = static_cast<HWND>(g_window->handler);
	ShowWindow(hwnd, SW_SHOWDEFAULT);
	UpdateWindow(hwnd);
}

void azorDestroyWindow()
{
	assert(g_window != nullptr);

	DestroyWindow(static_cast<HWND>(g_window->handler));
	UnregisterClass(g_window->title, wcex.hInstance);

	delete g_window;
	g_window = nullptr;
}
