#include "PathNode.h"

PathNode::PathNode()
{
}

PathNode::~PathNode()
{
	if (parent)
	{
		delete parent;
		parent = nullptr;
	}
}