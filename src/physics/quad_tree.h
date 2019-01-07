#ifndef QUAD_TREE_H
#define QUAD_TREE_H

#include "aabb.h"
#include "rigidbody.h"
#include <vector>
#include <map>

#define MAX_LEVEL                5
#define MAX_OBJECT_IN_REGION     4

typedef std::vector<AZORbody> BodyList;

typedef class QuadTree
{
public:
	explicit QuadTree(int level, AABB region);
	~QuadTree();

	void Clear();
	void Insert(AZORbody body);

	std::map<AZORbody, BodyList>& Query(BodyList& list);
	void Query(BodyList& list, AZORbody body);
	// BodyList& GetBodies();

private:
	bool		IsContain(AZORbody body) const;
	void		Split();

	int			level_;
	AABB		region;
	BodyList	bodies_;
	QuadTree**	nodes_;

} QuadTree, *AZORquadtree;

#endif // QUAD_TREE_H

