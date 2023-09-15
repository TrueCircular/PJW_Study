#include "TQuadTree.h"


void TQuadTree::BuildNode(TNode* node)
{
	if (SubDivide(node))
	{
		for (int i = 0; i < node->_childList.size(); i++)
		{

		}
	}
}

TNode* TQuadTree::CreateNode(TNode* parent, float topLeft, float topRight, float bottomLeft, float bottomRight)
{
	TNode* nNode = new TNode();

	nNode->_childList.reserve(4);
	nNode->_cornerList.reserve(4);

	nNode->_box._min = TVector3(topLeft, 0.f, bottomLeft);
	nNode->_box._max = TVector3(topRight, 0.f, bottomRight);
	nNode->_box._center = (nNode->_box._max + nNode->_box._min);
	nNode->_box._center /= 2.0f;
	nNode->_box._extent[0] = nNode->_box._max.x - nNode->_box._center.x;
	nNode->_box._extent[1] = nNode->_box._max.y - nNode->_box._center.y;
	nNode->_box._extent[2] = nNode->_box._max.z - nNode->_box._center.z;

	nNode->_cornerList.push_back(TVector3(nNode->_box._min.x, 0.0f, nNode->_box._max.z));
	nNode->_cornerList.push_back(nNode->_box._max);
	nNode->_cornerList.push_back(nNode->_box._min);
	nNode->_cornerList.push_back(TVector3(nNode->_box._max.x, 0.0f, nNode->_box._min.z));

	if (parent)
	{
		nNode->_depth = parent->_depth + 1;
		if (_maxLevel < nNode->_depth)
		{
			_maxLevel = nNode->_depth;
		}
	}

	return nNode;
}

bool TQuadTree::SubDivide(TNode* node)
{
	if (node == nullptr)
		return false;

	if (_maxLevel <= node->_depth)
	{
		node->_isLeaf = true;
		return false;
	}

	float splitWidth = (node->_cornerList[1].x - node->_cornerList[0].x) / 2;
	float splitHeight = (node->_cornerList[0].z - node->_cornerList[2].z) / 2;

	if (splitWidth < _minDivideSize || splitHeight < _minDivideSize)
	{
		node->_isLeaf = true;
		return false;
	}

	node->_childList.push_back(CreateNode(node, node->_cornerList[0].x, node->_cornerList[0].x + splitWidth,
		node->_cornerList[0].z - splitHeight, node->_cornerList[0].z));
	node->_childList.push_back(CreateNode(node, node->_cornerList[0].x + splitWidth, node->_cornerList[1].x,
		node->_cornerList[0].z - splitHeight, node->_cornerList[0].z));
	node->_childList.push_back(CreateNode(node, node->_cornerList[0].x, node->_cornerList[0].x + splitWidth,
		node->_cornerList[2].z, node->_cornerList[0].z - splitHeight));
	node->_childList.push_back(CreateNode(node, node->_cornerList[0].x + splitWidth, node->_cornerList[1].x,
		node->_cornerList[3].z, node->_cornerList[0].z - splitHeight));

	return true;
}

void TQuadTree::BuildTree(std::vector<PT_Vertex> vList, DWORD width, DWORD height)
{
	_mapWidth = width;
	_mapHeight = height;
}
void TQuadTree::Frame()
{

}
void TQuadTree::Render()
{

}
void TQuadTree::Release()
{

}