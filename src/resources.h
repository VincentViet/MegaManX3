#ifndef RESOURCES_H
#define RESOURCES_H

#include <common/settings.h>
#include "render.h"

typedef struct Texture
{
	uint32 width;
	uint32 height;
	LPDIRECT3DTEXTURE9 data;
}Texture, *AZORTexture;

#ifdef __cplusplus
extern "C"
{
#endif
bool		azorLoadTextureFromFile(const char* file_name, const char* alias);
AZORTexture	azorGetTexture(const char* alias);
void		azorClearResources(void);
#ifdef __cplusplus
}
#endif
#endif // RESOURCES_H
