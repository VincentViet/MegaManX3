#include "collisions.h"
#include <limits>

float32 SweptAABB(AZORbody one, AZORbody two, ContactData* data)
{
	const AABB b1 = one->GetAABB();
	const AABB b2 = two->GetAABB();

	float xInvEntry, yInvEntry;
	float xInvExit, yInvExit;

	// find the distance between the objects on the near and far sides for both x and y
	if (one->vel.x > 0.0f)
	{
		xInvEntry = b2.x - (b1.x + b1.width);
		xInvExit = (b2.x + b2.width) - b1.x;
	}
	else
	{
		xInvEntry = (b2.x + b2.width) - b1.x;
		xInvExit = b2.x - (b1.x + b1.width);
	}

	if (one->vel.y > 0.0f)
	{
		yInvEntry = b2.y - (b1.y + b1.height);
		yInvExit = (b2.y + b2.height) - b1.y;
	}
	else
	{
		yInvEntry = (b2.y + b2.height) - b1.y;
		yInvExit = b2.y - (b1.y + b1.height);
	}

	float xEntry, yEntry;
	float xExit, yExit;

	if (one->vel.x == 0.0f)
	{
		xEntry = -std::numeric_limits<float32>::infinity();
		xExit = std::numeric_limits<float32>::infinity();
	}
	else
	{
		xEntry = xInvEntry / one->vel.x;
		xExit = xInvExit / one->vel.x;
	}

	if (one->vel.y == 0.0f)
	{
		yEntry = -std::numeric_limits<float32>::infinity();
		yExit = std::numeric_limits<float32>::infinity();
	}
	else
	{
		yEntry = yInvEntry / one->vel.y;
		yExit = yInvExit / one->vel.y;
	}

	float entryTime = b2Max(xEntry, yEntry);
	float exitTime = b2Min(xExit, yExit);

	if (entryTime > exitTime || xEntry < 0.0f && yEntry < 0.0f || xEntry > 1.0f || yEntry > 1.0f)
	{
		data->normal.x = 0.0f;
		data->normal.y = 0.0f;
		data->IsCollided = false;
		data->first = data->second = nullptr;
		return 1.0f;
	}
	else // if there was a collision
	{
		data->IsCollided = true;
		data->first = one;
		data->second = two;

		// calculate normal of collided surface
		if (xEntry > yEntry)
		{
			if (xInvEntry < 0.0f)
			{
				data->normal.x = 1.0f;
				data->normal.y = 0.0f;
			}
			else
			{
				data->normal.x = -1.0f;
				data->normal.y = 0.0f;
			}
		}
		else
		{
			if (yInvEntry < 0.0f)
			{
				data->normal.x = 0.0f;
				data->normal.y = 1.0f;
			}
			else
			{
				data->normal.x = 0.0f;
				data->normal.y = -1.0f;
			}
		}

		// return the time of collision
		return entryTime;
	}
}
