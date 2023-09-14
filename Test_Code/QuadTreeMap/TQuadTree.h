#pragma once
#include "TStd.h"
#include "TDxObject.h"

struct T_BOX
{
	TVector3 _center;
	//aabb
	TVector3 _min;
	TVector3 _max;
	//obb
	TVector3 _axis[3];
	float	 _extent[3];
};

class TNode
{
public:
	DWORD				  _depth;
	bool				  _isLeaf;
	T_BOX				  _box;
	std::vector<TVector3> _cornerList;
	std::vector<TNode*>	  _childList;
public:
	TNode();
	~TNode();
};

class TQuadTree
{
public:
	std::vector<PT_Vertex> _vertexList;
	std::shared_ptr<TNode> _root;
public:
	void BuildTree(TNode* node);
	TNode* BuildNode();
};

