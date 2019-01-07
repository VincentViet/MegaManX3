#ifndef WINDOW_H
#define WINDOW_H

#include <common/math.h>
#include <Windows.h>

typedef struct Window
{
	void Show() const;

	uint32 x;
	uint32 y;
	uint32 width;
	uint32 height;
	const char* title;
	HWND handler;
} Window, *AZORwindow;

#ifdef __cplusplus
extern "C"
{
#endif

AZORwindow	azorGetWindow(void);
void		azorDestroyWindow(void);

#ifdef __cplusplus
}
#endif
#endif // WINDOW_H
