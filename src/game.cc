#include "resources.h"
#include "scenes.h"
#include "megaman.h"
#include "helit.h"
#include "notorbanger.h"
#include "headgunner.h"
#include "genji.h"
#include "blasthornet.h"
#include "camera.h"
#include "ground.h"
#include <vector>
#include "wall.h"

static AZORscene g_scene;
static Megaman* megaman;
static Helit* helit;
static Notorbanger* notorbanger;
static Headgunner* headgunner;
static Genji* genji;
static Blasthornet* blasthornet;

static std::vector<Ground*> grounds;
static std::vector<Wall*> walls;

void LoadResources()
{
	azorLoadTextureFromFile("background.png", "bg");
	azorLoadTextureFromFile("x_sprites.png", "megaman");
	azorLoadTextureFromFile("x3_helit.png", "helit");
	azorLoadTextureFromFile("x3_explosions.png", "explode");
	azorLoadTextureFromFile("x3_notorbanger.png", "notorbanger");
	azorLoadTextureFromFile("x3_headgunnercustomer.png", "headgunner");
	azorLoadTextureFromFile("x3_subboss_genjibo.png", "genji");
	azorLoadTextureFromFile("x3_blasthornet.png", "blasthornet");

	g_scene = azorGetScene();
}


void InitializeMap()
{	
	megaman = new Megaman;
	g_scene->AddObject(megaman);
	azorGetCamera()->Follow(megaman);

	helit = new Helit;
	helit->body_decs.position = b2Vec2{ 700, 450 };
	g_scene->AddObject(helit);

	notorbanger = new Notorbanger;
	notorbanger->body_decs.position = b2Vec2{ 500 , 500 };
	g_scene->AddObject(notorbanger);

	headgunner = new Headgunner;
	headgunner->body_decs.position = b2Vec2{ 600, 500 };
	g_scene->AddObject(headgunner);

	genji = new Genji;
	g_scene->AddObject(genji);

	blasthornet = new Blasthornet;
	g_scene->AddObject(blasthornet);

#pragma region Map
	grounds.push_back(new Ground(Vec2{ 0 + 842.0f / 2, 953 }, 842, 0));
	grounds.push_back(new Ground(Vec2{ 347 + 282 / 2, 905 }, 282, 0));
	grounds.push_back(new Ground(Vec2{ 508 + 123 / 2, 858 }, 123, 0));
	grounds.push_back(new Ground(Vec2{ 0 + 244 / 2, 837 }, 244, 0));
	grounds.push_back(new Ground(Vec2{ 252 + 122 / 2, 822 }, 122, 0));
	grounds.push_back(new Ground(Vec2{ 379 + 412 / 2, 789 }, 412, 0));
	grounds.push_back(new Ground(Vec2{ 939 + 78 / 2, 957 }, 78, 0));
	grounds.push_back(new Ground(Vec2{ 798 + 44 / 2, 698 }, 44, 0));
	grounds.push_back(new Ground(Vec2{ 939 + 47 / 2, 697 }, 47, 0));
	grounds.push_back(new Ground(Vec2{ 790 + 51 / 2, 443 }, 51, 0));
	grounds.push_back(new Ground(Vec2{ 940 + 145 / 2, 443 }, 145, 0));
	grounds.push_back(new Ground(Vec2{ 796 + 193 / 2, 280 }, 193, 0));
	grounds.push_back(new Ground(Vec2{ 989 + 269 / 2, 294 }, 269, 0));
	grounds.push_back(new Ground(Vec2{ 379 + 412 / 2, 789 }, 412, 0));
	grounds.push_back(new Ground(Vec2{ 1085 + 91 / 2, 395 }, 91, 0));
	grounds.push_back(new Ground(Vec2{ 1178 + 61 / 2, 427 }, 61, 0));
	grounds.push_back(new Ground(Vec2{ 1260 + 43 / 2, 326 }, 43, 0));
	grounds.push_back(new Ground(Vec2{ 1242 + 446 / 2, 458 }, 446, 0));
	grounds.push_back(new Ground(Vec2{ 1388 + 115 / 2, 203 }, 115, 0));
	grounds.push_back(new Ground(Vec2{ 1308 + 188 / 2, 37 }, 188, 0));
	grounds.push_back(new Ground(Vec2{ 1388 + 219 / 2, 356 }, 219, 0));
	grounds.push_back(new Ground(Vec2{ 1610 + 658 / 2, 293 }, 658, 0));
	grounds.push_back(new Ground(Vec2{ 2013 + 250 / 2, 426 }, 250, 0));
	grounds.push_back(new Ground(Vec2{ 2076 + 41 / 2, 347 }, 41, 0));
	grounds.push_back(new Ground(Vec2{ 1563 + 60 / 2, 699 }, 60, 0));
	grounds.push_back(new Ground(Vec2{ 1932 + 60 / 2, 827 }, 60, 0));
	grounds.push_back(new Ground(Vec2{ 1564 + 59 / 2, 955 }, 59, 0));
	grounds.push_back(new Ground(Vec2{ 1563 + 62 / 2, 1211 }, 62, 0));
	grounds.push_back(new Ground(Vec2{ 1709 + 107 / 2, 1131 }, 107, 0));
	grounds.push_back(new Ground(Vec2{ 1819 + 60 / 2, 1162 }, 60, 0));
	grounds.push_back(new Ground(Vec2{ 1708 + 286 / 2, 726 }, 286, 0));
	grounds.push_back(new Ground(Vec2{ 1562 + 317 / 2, 853 }, 317, 0));
	grounds.push_back(new Ground(Vec2{ 1708 + 288 / 2, 982 }, 288, 0));
	grounds.push_back(new Ground(Vec2{ 1882 + 4094 / 2, 1211 }, 4094, 0));
	grounds.push_back(new Ground(Vec2{ 2269 + 41 / 2, 1157 }, 41, 0));
	grounds.push_back(new Ground(Vec2{ 2013 + 253 / 2, 1079 + 13 / 2 }, 43, 0));
	grounds.push_back(new Ground(Vec2{ 2315 + 227 / 2, 1045 }, 227, 0));
	grounds.push_back(new Ground(Vec2{ 2541 + 332 / 2, 1157 }, 332, 0));
	grounds.push_back(new Ground(Vec2{ 5324 + 62 / 2, 1077 }, 62, 0));
	grounds.push_back(new Ground(Vec2{ 5389 + 251 / 2, 1157 }, 251, 0));
	grounds.push_back(new Ground(Vec2{ 5643 + 227 / 2, 1044 }, 227, 0));
	grounds.push_back(new Ground(Vec2{ 5868 + 42 / 2, 1156 }, 42, 0));
	grounds.push_back(new Ground(Vec2{ 5980 + 58 / 2, 1163 }, 58, 0));
	grounds.push_back(new Ground(Vec2{ 5916 + 190 / 2, 1061 }, 190, 0));
	grounds.push_back(new Ground(Vec2{ 5917 + 120 / 2, 1301 }, 120, 0));
	grounds.push_back(new Ground(Vec2{ 5901 + 10 / 2, 1318 }, 10, 0));
	grounds.push_back(new Ground(Vec2{ 5948 + 173 / 2, 1413 }, 173, 0));
	grounds.push_back(new Ground(Vec2{ 5932 + 122 / 2, 1511 }, 122, 0));
	grounds.push_back(new Ground(Vec2{ 5965 + 121 / 2, 1606 }, 121, 0));
	grounds.push_back(new Ground(Vec2{ 5916 + 139 / 2, 1702 }, 139, 0));
	grounds.push_back(new Ground(Vec2{ 5980 + 125 / 2, 1797 }, 125, 0));
	grounds.push_back(new Ground(Vec2{ 5980 + 523 / 2, 1977 }, 523, 0));
	grounds.push_back(new Ground(Vec2{ 6557 + 1357 / 2, 1978 }, 1357, 0));
	grounds.push_back(new Ground(Vec2{ 6107 + 374 / 2, 1860 }, 374, 0));
	grounds.push_back(new Ground(Vec2{ 6574 + 119 / 2, 1860 }, 119, 0));
	grounds.push_back(new Ground(Vec2{ 6780 + 121 / 2, 1860 }, 121, 0));
	grounds.push_back(new Ground(Vec2{ 6989 + 138 / 2, 1860 }, 138, 0));
	grounds.push_back(new Ground(Vec2{ 7133 + 58 / 2, 1844 }, 58, 0));
	grounds.push_back(new Ground(Vec2{ 7196 + 190 / 2, 1828 }, 190, 0));
	grounds.push_back(new Ground(Vec2{ 7388 + 301 / 2, 1925 }, 301, 0));
	grounds.push_back(new Ground(Vec2{ 7690 + 222 / 2, 1815 }, 222, 0));

	walls.push_back(new Wall(Vec2{ 0, 837 + 242 / 2 }, 0, 242));
	walls.push_back(new Wall(Vec2{ 250, 820 + 17 / 2 }, 0, 17));
	walls.push_back(new Wall(Vec2{ 376, 787 + 32 / 2 }, 0, 32));
	walls.push_back(new Wall(Vec2{ 348, 909 + 45 / 2 }, 0, 45));
	walls.push_back(new Wall(Vec2{ 508, 861 + 44 / 2 }, 0, 44));
	walls.push_back(new Wall(Vec2{ 633, 859 + 95 / 2 }, 0, 95));
	walls.push_back(new Wall(Vec2{ 840, 956 + 52 / 2 }, 0, 52));
	walls.push_back(new Wall(Vec2{ 938, 954 + 52 / 2 }, 0, 52));
	walls.push_back(new Wall(Vec2{ 795, 281 + 503 / 2 }, 0, 503));
	walls.push_back(new Wall(Vec2{ 987, 443 + 564 / 2 }, 0, 564));
	walls.push_back(new Wall(Vec2{ 1084, 395 + 45 / 2 }, 0, 45));
	walls.push_back(new Wall(Vec2{ 1176, 396 + 35 / 2 }, 0, 35));
	walls.push_back(new Wall(Vec2{ 1238, 429 + 29 / 2 }, 0, 29));
	walls.push_back(new Wall(Vec2{ 1259, 295 + 29 / 2 }, 0, 29));
	walls.push_back(new Wall(Vec2{ 1304, 37 + 284 / 2 }, 0, 284));
	walls.push_back(new Wall(Vec2{ 1388, 205 + 153 / 2 }, 0, 153));
	walls.push_back(new Wall(Vec2{ 1498, 38 + 163 / 2 }, 0, 163));
	walls.push_back(new Wall(Vec2{ 1607, 293 + 59 / 2 }, 0, 59));
	walls.push_back(new Wall(Vec2{ 2269, 293 + 132 / 2 }, 0, 132));
	walls.push_back(new Wall(Vec2{ 2076, 349 + 75 / 2 }, 0, 75));
	walls.push_back(new Wall(Vec2{ 2118, 347 + 78 / 2 }, 0, 78));
	walls.push_back(new Wall(Vec2{ 1688, 459 + 92 / 2 }, 0, 92));
	walls.push_back(new Wall(Vec2{ 1999, 431 + 598 / 2 }, 0, 598));
	walls.push_back(new Wall(Vec2{ 1558, 583 + 629 / 2 }, 0, 629));
	walls.push_back(new Wall(Vec2{ 1625, 1213 + 60 / 2 }, 0, 60));
	walls.push_back(new Wall(Vec2{ 1709, 1130 + 148 / 2 }, 0, 148));
	walls.push_back(new Wall(Vec2{ 1815, 1131 + 31 / 2 }, 0, 31));
	walls.push_back(new Wall(Vec2{ 1879, 1164 + 54 / 2 }, 0, 54));
	walls.push_back(new Wall(Vec2{ 2012, 1033 + 56 / 2 }, 0, 56));
	walls.push_back(new Wall(Vec2{ 2270, 1093 + 63 / 2 }, 0, 63));
	walls.push_back(new Wall(Vec2{ 2312, 1047 + 109 / 2 }, 0, 109));
	walls.push_back(new Wall(Vec2{ 2041, 1045 + 108 / 2 }, 0, 108));
	walls.push_back(new Wall(Vec2{ 2872, 779 + 377 / 2 }, 0, 377));
	walls.push_back(new Wall(Vec2{ 5324, 859 + 218 / 2 }, 0, 218));
	walls.push_back(new Wall(Vec2{ 5389, 1078 + 74 / 2 }, 0, 74));
	walls.push_back(new Wall(Vec2{ 5640, 1044 + 109 / 2 }, 0, 109));
	walls.push_back(new Wall(Vec2{ 5868, 1047 + 108 / 2 }, 0, 108));
	walls.push_back(new Wall(Vec2{ 5911, 1063 + 93 / 2 }, 0, 93));
	walls.push_back(new Wall(Vec2{ 5980, 1163 + 51 / 2 }, 0, 51));
	walls.push_back(new Wall(Vec2{ 6038, 1164 + 137 / 2 }, 0, 137));
	walls.push_back(new Wall(Vec2{ 5914, 1303 + 14 / 2 }, 0, 14));
	walls.push_back(new Wall(Vec2{ 6109, 1063 + 323 / 2 }, 0, 323));
	walls.push_back(new Wall(Vec2{ 5896, 1318 + 381 / 2 }, 0, 381));
	walls.push_back(new Wall(Vec2{ 6123, 1414 + 359 / 2 }, 0, 359));
	walls.push_back(new Wall(Vec2{ 5913, 1703 + 351 / 2 }, 0, 351));
	walls.push_back(new Wall(Vec2{ 6109, 1798 + 62 / 2 }, 0, 62));
	walls.push_back(new Wall(Vec2{ 5980, 1978 + 75 / 2 }, 0, 75));
	walls.push_back(new Wall(Vec2{ 6504, 1979 + 72 / 2 }, 0, 72));
	walls.push_back(new Wall(Vec2{ 6557, 1979 + 71 / 2 }, 0, 71));
	walls.push_back(new Wall(Vec2{ 6487, 1401 + 59 / 2 }, 0, 59));
	walls.push_back(new Wall(Vec2{ 7390, 1830 + 93 / 2 }, 0, 93));
	walls.push_back(new Wall(Vec2{ 7687, 1816 + 52 / 2 }, 0, 52));
	walls.push_back(new Wall(Vec2{ 7915, 1815 + 166 / 2 }, 0, 166));
#pragma endregion

	for (auto&& ground : grounds)
	{
		g_scene->AddObject(ground);
	}

	for (auto&& wall : walls)
	{
		g_scene->AddObject(wall);
	}
}

void CleanUp()
{
	for (auto&& ground : grounds)
	{
		delete ground;
	}

	for (auto&& wall : walls)
	{
		delete wall;
	}

	delete megaman;
}