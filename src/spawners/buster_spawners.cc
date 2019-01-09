#include "buster_spawners.h"
#include "../scenes.h"
#include "../bullets/busters/small_buster.h"

static AZORscene g_scene = nullptr;

BusterSpawner::BusterSpawner(Vec2 offset, Object* owner)
{
	this->offset = offset;
	this->owner = owner;
	g_scene = azorGetScene();

	for(uint8 index = 0; index < 10; index++)
	{
		small_busters_.push_back(new SmallBuster);
		g_scene->AddObject(small_busters_[index]);
	}
}

BusterSpawner::~BusterSpawner()
{
	for (auto&& buster : small_busters_)
	{
		delete buster;
	}

	for (auto&& buster : medium_busters_)
	{
		delete buster;
	}

	for (auto&& buster : large_busters_)
	{
		delete buster;
	}
}

void BusterSpawner::Shoot(const BulletType type)
{
	switch (type)
	{
	case BulletType::SMALL_BUSTER:
		ShootSmallBuster();
		break;

	case BulletType::MEDIUM_BUSTER:
		ShootMediumBuster();
		break;

	case BulletType::LARGE_BUSTER:
		ShootLargeBuster();
		break;
	default: break;
	}
}

void BusterSpawner::ShootSmallBuster()
{
	for (auto&& buster : small_busters_)
	{
		if (!buster->body->IsActive())
		{
			buster->body->SetTransform(position, 0.0f);
			buster->direction = owner->direction;
			buster->body->SetActive(true);
			break;
		}
	}
}

void BusterSpawner::ShootMediumBuster()
{
}

void BusterSpawner::ShootLargeBuster()
{
}
