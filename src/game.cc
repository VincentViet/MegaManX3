#include "resources.h"
#include "scenes.h"
#include "megaman.h"
#include "camera.h"
#include "ground.h"
#include <vector>


static AZORscene g_scene;
static Megaman* megaman;
static std::vector<Ground*> grounds;

void LoadResources()
{
	azorLoadTextureFromFile("background.png", "bg");
	azorLoadTextureFromFile("x_sprites.png", "megaman");
	g_scene = azorGetScene();
}


void InitializeMap()
{	
	megaman = new Megaman;
	g_scene->AddObject(megaman);
	azorGetCamera()->Follow(megaman);

	grounds.push_back(new Ground(Vec2{ 0 + 842.0f / 2, 953 }, 842, 0));

	for (auto&& ground : grounds)
	{
		g_scene->AddObject(ground);
	}
}

void CleanUp()
{
	delete megaman;
}