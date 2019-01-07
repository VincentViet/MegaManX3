#define  _CRT_SECURE_NO_WARNINGS
#include "resources.h"
#include <jansson/jansson.h>
#include <map>
#include <string>
#include <dx9/d3dx9.h>

static Renderer* g_renderer = nullptr;
static std::map<const std::string, AZORTexture> textures;

bool azorLoadTextureFromFile(const char* file_name, const char* alias)
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
		return false;
	}

	g_renderer = azorGetRenderer();
	if (g_renderer)
	{
		const auto resources_configs =
			json_object_get(configs, "Resources");
		const auto sprites_path =
			json_string_value(json_object_get(resources_configs, "sprites_path"));

		char path[50];
		strcpy(path, sprites_path);
		strcat(path, file_name);

		D3DXIMAGE_INFO info;
		const auto texture = new Texture;
		memset(texture, 0, sizeof(Texture));

		D3DXCreateTextureFromFileEx(
			g_renderer->device9,
			path,
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT,
			D3DUSAGE_RENDERTARGET,
			D3DFMT_UNKNOWN,
			D3DPOOL_DEFAULT,
			D3DX_DEFAULT,
			D3DX_DEFAULT,
			0,
			&info,
			nullptr,
			&texture->data);

		if (!texture->data)
			return false;

		texture->width = info.Width;
		texture->height = info.Height;
		textures.insert(std::pair<const char*, AZORTexture>(alias, texture));
		return true;
	}

	return false;
}

AZORTexture azorGetTexture(const char* alias)
{
	try
	{
		return textures.at(alias);
	}
	catch (...)
	{
		return nullptr;
	}
}

void azorClearResources()
{
	for (auto&& texture : textures)
	{
		texture.second->data->Release();
		delete texture.second;
	}

	textures.clear();
}
