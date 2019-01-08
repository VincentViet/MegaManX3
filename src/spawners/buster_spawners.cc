#include "buster_spawners.h"
#include "../scenes.h"
#include "../bullets/busters/small_buster.h"

static AZORscene g_scene = nullptr;

SmallBusterSpawner::SmallBusterSpawner(Vec2 offset, Object* owner)
{
	this->offset = offset;
	this->owner = owner;
	g_scene = azorGetScene();

	for(uint8 index = 0; index < 10; index++)
	{
		bullets_.push_back(new SmallBuster);
		g_scene->AddObject(bullets_[index]);
	}
}

SmallBusterSpawner::~SmallBusterSpawner()
{
	for (auto&& bullet : bullets_)
	{
		delete bullet;
	}
}

void SmallBusterSpawner::Shoot() const
{
	// static Vec2 pos;
	for (auto&& bullet : bullets_)
	{
		if (!bullet->body->IsActive())
		{
			bullet->body->SetTransform(position, 0.0f);
			bullet->direction = owner->direction;
			bullet->body->SetActive(true);
			break;
		}
	}
}
