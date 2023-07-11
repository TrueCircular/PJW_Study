#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<queue>

using namespace std;

struct QtNode
{
	bool isLeaf;
	vector<QtNode*> child;

	QtNode() : isLeaf(true)
	{
		child.resize(4, nullptr);
	}
};

class QTree
{
private:
	queue<QtNode*> _queue;
	QtNode* _root;
public:
	QtNode* GetRootnode()const { return _root; }
private:
	void BuildTree(QtNode* node);
	QtNode* CreateNode(QtNode* parent, float x, float y, float width, float height);
public:
	void BuildQuadTree();
	QtNode* AddObject()
public:
	~QTree() { delete _root; }

};

