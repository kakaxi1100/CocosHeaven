#pragma once

class PathNode
{
public:
	PathNode();
	~PathNode();

	PathNode* parent;
	bool isChecked;
private:

};

