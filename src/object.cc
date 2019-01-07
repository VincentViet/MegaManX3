#include "object.h"
#include <jansson/jansson.h>
#include "debug.h"
#include "camera.h"

static AZORcamera g_camera;
static Vec2 gravity;

Object::Object(): tag(Tag::UNKNOWN)
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
		gravity.y = 10.0f;
	}
	else
	{
		const auto physic_configs = json_object_get(configs, "Physics");
		gravity.y =
			json_real_value(json_object_get(physic_configs, "gravity"));
	}

	g_camera = azorGetCamera();
}

Object::Object(Tag tag)
	:tag(tag)
{}

void Object::Update()
{
	this->position += Debug::delta_time * vel;
	if (is_jumping)
	{
		this->vel += Debug::delta_time * gravity;
	}
}

void Object::ChangeState(State* state)
{
	this->state = state;
	this->state->owner = this;
}

Rect& Object::GetBound()
{
	static Rect result;
	return result;
}

Vec2 Object::GetPosition() const
{
	return position;
}
