#include "input.h"
#include <common/settings.h>

typedef struct
{
	IDirectInputDevice8* device;
	char data[256];
} InputDevice;

static InputDevice* g_keyboard;

void azorPollInput(HWND hwnd)
{
	if (!g_keyboard)
	{
		IDirectInput8* dinput8 = nullptr;

		g_keyboard = static_cast<InputDevice*>(malloc(sizeof(InputDevice)));
		memset(g_keyboard, 0, sizeof(InputDevice));
		// g_keyboard->data = malloc(256 * sizeof(char));
		// memset(g_keyboard->data, 0, 256 * sizeof(char));

		if (FAILED(DirectInput8Create(
			GetModuleHandle(nullptr),
			DIRECTINPUT_VERSION,
			IID_IDirectInput8,
			reinterpret_cast<void**>(&dinput8),
			nullptr)))
		{
			//print error
			return;
		}

		if (FAILED(dinput8->CreateDevice(
			GUID_SysKeyboard,
			&g_keyboard->device,
			nullptr)))
		{
			//print error
			dinput8->Release();
			return;
		}
		g_keyboard->device->SetDataFormat(&c_dfDIKeyboard);
		g_keyboard->device->SetCooperativeLevel(hwnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
		dinput8->Release();
	}

	if (g_keyboard->device)
	{
		if (FAILED(
			g_keyboard->device->GetDeviceState(
				sizeof g_keyboard->data,
				static_cast<void*>(&g_keyboard->data))))
		{
			ZeroMemory(g_keyboard->data, sizeof g_keyboard->data);
			g_keyboard->device->Acquire();
		}
	}
}

bool azorIsKeyDown(Keys key)
{
	return g_keyboard->data[static_cast<int32>(key)] & 0x80;
}

void azorDestroyInput()
{
	assert(g_keyboard != nullptr);
	g_keyboard->device->Unacquire();
	g_keyboard->device->Release();
	free(g_keyboard);
	g_keyboard = nullptr;
}

bool azorIsKeyUp(Keys key)
{
	return !(g_keyboard->data[static_cast<int32>(key)] & 0x80);
}
