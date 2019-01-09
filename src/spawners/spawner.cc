#include "spawner.h"

void Spawner::Update()
{
	position.x =
		owner->body->GetPosition().x + offset.x * owner->direction;

	position.y = owner->body->GetPosition().y;
}
