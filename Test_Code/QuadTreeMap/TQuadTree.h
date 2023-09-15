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
	TNode*				  _parent;
	std::vector<TVector3> _cornerList;
	std::vector<TNode*>	  _childList;
public:
	TNode();
	~TNode();
};

class TQuadTree
{
private:
	std::vector<PT_Vertex> _vertexList;
	std::vector<DWORD>     _indexList;
	TNode*				   _root;
	DWORD				   _mapWidth;
	DWORD			       _mapHeight;

	DWORD				   _maxLevel;
	float				   _minDivideSize;
	float				   _maxDivideSize;
private:
	void	BuildNode(TNode* node);
	TNode*	CreateNode(TNode* parent, float topLeft, float topRight, float bottomLeft, float bottomRight);
	bool	SubDivide(TNode* node);
public:
	void	BuildTree(std::vector<PT_Vertex> vList, DWORD width, DWORD height);
public:
	void	Frame();
	void	Render();
	void	Release();
};

