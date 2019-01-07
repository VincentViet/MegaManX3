#ifndef SCENES_H
#define SCENES_H

#include "object.h"

struct ObjectNode
{
	Object* object;
	int32	next;
};

struct ObjectPool
{
	int32	GetNode();
	void	ReturnNode(int32 id);

	ObjectNode* operator[](const uint32 id) const
	{
		return &nodes[id];
	}

	ObjectPool();
	~ObjectPool();

	ObjectNode* nodes{};
	int32 size;
	int32 capacity;
	int32 using_nodes;
	int32 free_nodes;
};

typedef struct Scene
{
	void AddObject(Object* object);
	void RemoveObject(Object* object);
	void Start(void) const;
	void Update(void) const;
	void Draw(void) const;

	int32 head{};
	ObjectPool pool;
} Scene, *AZORscene;

AZORscene	azorGetScene(void);
void		azorDestroyScene(void);
// void		azorStartScene(void);
// void		azorUpdateScene(void);

#endif // SCENES_H
