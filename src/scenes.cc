#include "scenes.h"
#include <cstring>
#include <cstdlib>
#include "physics.h"

static AZORscene g_scene = nullptr;
static AZORphysics g_physics = nullptr;

int32 ObjectPool::GetNode()
{
	if (free_nodes == NULL_NODE)
	{
		assert(size == capacity);

		const auto old_nodes = nodes;
		capacity *= 2;
		nodes = static_cast<ObjectNode*>(malloc(capacity * sizeof(ObjectNode)));
		memcpy(nodes, old_nodes, size * sizeof(ObjectNode));
		free(old_nodes);

		for (auto i = size; i < capacity - 1; i++)
			nodes[i].next = i + 1;

		nodes[capacity - 1].next = NULL_NODE;
		free_nodes = size;
	}

	const auto node_id = free_nodes;
	free_nodes = nodes[node_id].next;
	nodes[node_id].next = using_nodes;
	using_nodes = node_id;
	size++;

	return node_id;
}

void ObjectPool::ReturnNode(const int32 id)
{
	assert(0 <= id && id < capacity);
	assert(size > 0);

	auto node = using_nodes;
	auto prev = NULL_NODE;
	while (node != NULL_NODE)
	{
		if (node == id)
		{
			if (prev == NULL_NODE)
				using_nodes = nodes[node].next;
			else
				nodes[prev].next = nodes[node].next;
		}
		prev = node;
		node = nodes[node].next;
	}

	nodes[id].next = free_nodes;
	free_nodes = id;
	size--;
}

ObjectPool::ObjectPool()
{
	capacity = 16;
	size = 0;
	nodes = static_cast<ObjectNode*>(malloc(capacity * sizeof ObjectNode));
	memset(nodes, 0, capacity * sizeof ObjectNode);

	for (auto i = 0; i < capacity - 1; ++i)
		nodes[i].next = i + 1;

	nodes[capacity - 1].next = NULL_NODE;
	free_nodes = 0;
	using_nodes = NULL_NODE;
}

ObjectPool::~ObjectPool()
{
	free(nodes);
}

void Scene::AddObject(Object* object)
{
	const auto new_node = pool.GetNode();
	pool[new_node]->object = object;
	object->id = new_node;
	object->body = 
		g_physics->CreateBody(&object->body_decs, &object->collider_decs);

	if (head == NULL_NODE)
	{
		head = new_node;
		pool[new_node]->next = NULL_NODE;
	}
	else
	{
		pool[new_node]->next = head;
		head = new_node;
	}
}

void Scene::RemoveObject(Object* object)
{
	// not correct
	// const auto id = object->id;
	// assert(0 <= id && id < pool.capacity);
	// assert(object->scene == this);
	//
	// azorRemoveBody(object->body);
	// delete object;
	// pool.ReturnNode(id);
}

void Scene::Start() const
{
	static int32 id;
	id = head;
	while (id != NULL_NODE)
	{
		pool[id]->object->Start();
		id = pool[id]->next;
	}
}

void Scene::Update() const
{
	static int32 id;
	id = head;
	while (id != NULL_NODE)
	{
		pool[id]->object->Update();
		id = pool[id]->next;
	}
}

void Scene::Draw() const
{
	static int32 id;
	id = head;
	while (id != NULL_NODE)
	{
		pool[id]->object->Draw();
		id = pool[id]->next;
	}
}

Scene* azorGetScene()
{
	if (!g_scene)
	{
		g_scene = new Scene;
		g_scene->head = -1;

		g_physics = azorGetPhysics();
	}

	return g_scene;
}

void azorDestroyScene()
{
	assert(g_scene != nullptr);
	delete g_scene;
	g_scene = nullptr;
}
