#include "quad_tree.h"

QuadTree::QuadTree(const int level, const AABB region)
	: level_(level), region(region), nodes_(nullptr)
{
}

QuadTree::~QuadTree()
{
	Clear();
}

void QuadTree::Clear()
{
	//Clear all nodes
	if (nodes_)
	{
		for (int i = 0; i < 4; i++)
		{
			nodes_[i]->Clear();
			delete nodes_[i];
		}
		delete[] nodes_;
	}

	//Clear current quadtree
	bodies_.clear();
}

void QuadTree::Insert(AZORbody body)
{
	//Insert entity into corresponding nodes
	if (nodes_)
	{
		if (nodes_[0]->IsContain(body))
			nodes_[0]->Insert(body);
		if (nodes_[1]->IsContain(body))
			nodes_[1]->Insert(body);
		if (nodes_[2]->IsContain(body))
			nodes_[2]->Insert(body);
		if (nodes_[3]->IsContain(body))
			nodes_[3]->Insert(body);

		return; // Return here to ignore rest.
	}

	//Insert entity into current quadtree
	if (this->IsContain(body))
		bodies_.push_back(body);

	//Split and move all objects in list into it’s corresponding nodes
	if (bodies_.size() > MAX_OBJECT_IN_REGION && level_ < MAX_LEVEL)
	{
		Split();

		while (!bodies_.empty())
		{
			if (nodes_[0]->IsContain(bodies_.back()))
				nodes_[0]->Insert(bodies_.back());
			if (nodes_[1]->IsContain(bodies_.back()))
				nodes_[1]->Insert(bodies_.back());
			if (nodes_[2]->IsContain(bodies_.back()))
				nodes_[2]->Insert(bodies_.back());
			if (nodes_[3]->IsContain(bodies_.back()))
				nodes_[3]->Insert(bodies_.back());

			bodies_.pop_back();
		}
	}
}

std::map<AZORbody, BodyList>& QuadTree::Query(BodyList& list)
{
	static std::map<AZORbody, BodyList> result;
	static BodyList bodies;
	result.clear();

	for (auto&& body : list)
	{
		bodies.clear();
		Query(bodies, body);
		for (auto&& value : bodies)
		{
			if (result.count(value))
				value = nullptr;
		}
		result.insert(std::pair<AZORbody, BodyList>{body, bodies});
	}

	return result;
}

void QuadTree::Query(BodyList& list, AZORbody body)
{
	if (nodes_)
	{
		if (nodes_[0]->IsContain(body))
			nodes_[0]->Query(list, body);
		if (nodes_[1]->IsContain(body))
			nodes_[1]->Query(list, body);
		if (nodes_[2]->IsContain(body))
			nodes_[2]->Query(list, body);
		if (nodes_[3]->IsContain(body))
			nodes_[3]->Query(list, body);

		return; // Return here to ignore rest.
	}

	//Add all entities in current region into return_objects_list
	if (this->IsContain(body))
	{
		for (auto& bodie : bodies_)
		{
			if (body != bodie)
				list.push_back(bodie);
		}
	}
}

// BodyList& QuadTree::GetBodies()
// {
// }

bool QuadTree::IsContain(AZORbody body) const
{
	const AABB bound = body->GetAABB();

	return !(bound.x + bound.width < region.x ||
		bound.y + bound.height < region.y ||
		bound.x > region.x + region.width ||
		bound.y > region.y + region.height);
}

void QuadTree::Split()
{
	nodes_ = new AZORquadtree[4];

	nodes_[0] = new QuadTree(level_ + 1,
	                         AABB{ region.x, region.y, region.width / 2, region.height / 2 });
	nodes_[1] = new QuadTree(level_ + 1,
	                         AABB{ region.x + region.width / 2, region.y, region.width / 2, region.height / 2 });
	nodes_[2] = new QuadTree(level_ + 1,
	                         AABB{ region.x, region.y + region.height / 2, region.width / 2, region.height / 2 });
	nodes_[3] = new QuadTree(level_ + 1,
	                         AABB{ region.x + region.width / 2,
		                         region.y + region.height / 2, region.width / 2, region.height / 2 });
}
