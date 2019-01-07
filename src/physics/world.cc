#include "world.h"
#include "collisions.h"
#include "../object.h"
#include <jansson/jansson.h>

World::World()
{
	tree_ = new QuadTree(1, AABB{ 0, 0, 7984, 2068 });

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

		gravity_ = 9.8f;
	}
	else
	{
		const auto physic_configs = json_object_get(configs, "Physics");
		gravity_ =
			json_real_value(json_object_get(physic_configs, "gravity"));
	}
}

World::~World()
{
	delete tree_;
}

AZORbody World::CreateBody(BodyDecs* decs)
{
	static AZORbody body;

	body = new Rigidbody(decs);
	body->vel += Vec2{ 0, -gravity_ };

	if (body->type == BodyType::DYNAMIC)
	{
		dynamic_.push_back(body);
	}

	bodies_.push_back(body);
	tree_->Insert(body);

	return body;
}

void World::Update(float32 time_step)
{
	static std::map<AZORbody, BodyList>* result;
	static ContactData data;

	for (auto&& dynamic : dynamic_)
	{
		dynamic->pos += time_step * dynamic->vel;
	}

	result = &tree_->Query(dynamic_);
	for (auto&& value : *result)
	{
		for (auto&& rigidbody : value.second)
		{
			if (rigidbody)
			{
				const auto remaining_time = SweptAABB(value.first, rigidbody, &data);
				if (data.IsCollided)
				{
					const auto a = static_cast<Object*>(data.first->object);
					const auto b = static_cast<Object*>(data.second->object);

					a->OnColliderEnter(b);
					b->OnColliderEnter(a);

					// perform response here
					if (data.second->type == BodyType::STATIC)
					{
						const float dotprod = 
							(data.first->vel.x * data.normal.y + data.first->vel.y * data.normal.x)
							* remaining_time;

						data.first->vel.x = dotprod * data.normal.y;
						data.first->vel.y = dotprod * data.normal.x;
					}
				}
			}
		}
	}
}
