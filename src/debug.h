#ifndef DEBUG_H
#define DEBUG_H

#include <common/settings.h>

struct Debug
{
	static void Log(const char* fmt, ...);

	static bool debug_mode;
	static float32 delta_time;
	static float32 total_time;
	static uint64 clear_color;
	static void* debug_draw;
};

void azorRenderDebug(void);
void azorDestroyDebug();

#endif // DEBUG_H
