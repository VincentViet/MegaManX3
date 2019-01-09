#include "bullet.h"

Bullet::Bullet() = default;

Bullet::~Bullet()
{
	delete sprite_;
}

void Bullet::SetActive(bool active) const
{
	this->body->SetActive(active);
}