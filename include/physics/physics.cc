#include "physics.h"
#include "common/settings.h"
#include <core/debug.h>
#include <janssson/jansson.h>
#include <core/object.h>

static World* g_world = nullptr;

class MyContactListener : public b2ContactListener
{
	void BeginContact(b2Contact* contact) override
	{
		const auto a = contact->GetFixtureA();
		const auto b = contact->GetFixtureB();

		const auto o_a = static_cast<Object*>(a->GetUserData());
		const auto o_b = static_cast<Object*>(b->GetUserData());

		o_a->OnColliderEnter(o_b);
		o_b->OnColliderEnter(o_a);
	}

	void EndContact(b2Contact* contact) override
	{
		const auto a = contact->GetFixtureA();
		const auto b = contact->GetFixtureB();

		const auto o_a = static_cast<Object*>(a->GetUserData());
		const auto o_b = static_cast<Object*>(b->GetUserData());

		o_a->OnColliderExit(o_b);
		o_b->OnColliderExit(o_a);
	}
};

static MyContactListener* contact_listener = nullptr;
static b2Draw* debug_draw = nullptr;

Rigidbody* azorCreateBody(BodyDecs* body_decs, ColliderDecs* col_decs)
{
	if (!g_world)
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
			return nullptr;
		}

		const auto physic_configs = json_object_get(configs, "Physics");
		const float32 gravity =
			json_real_value(json_object_get(physic_configs, "gravity"));
		g_world = new World(b2Vec2{ 0, gravity });

		contact_listener = new MyContactListener;
		g_world->SetContactListener(contact_listener);
		g_world->SetDebugDraw(reinterpret_cast<b2Draw*>(azorGetDebugDraw()));
	}

	const auto body = g_world->CreateBody(body_decs);
	body->CreateFixture(col_decs);

	return body;
}

void azorUpdatePhysics()
{
	assert(g_world != nullptr);
	g_world->Step(azorGetDeltaTime(), 6, 2);
	if (azorIsDebugModeOn())
	{
		g_world->DrawDebugData();
	}
}

void azorDestroyPhysics()
{
	assert(g_world != nullptr);
	delete g_world;
	g_world = nullptr;
}


