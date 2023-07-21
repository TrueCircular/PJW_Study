#pragma once
#include"../QNode/QNode.h"

using namespace std;

class QTree
{
private:
	QNode*			_root;
	queue<QNode*>	_queue;
public:
	QTree() : _root(nullptr) {}
	~QTree() { delete _root; }
public:
	bool	Init();
	bool	PreFrame();
	bool	Frame();
	bool	Render();
	bool	Release();
public:
	void	SetDefault();
	void	BuildTree();
	void	AddObject(E_ObjectType eType);
	QNode*	FindNode(QObject* fObj);
public:
	void	PreOrder();
	void	LevelOrder();
public:
	QNode* GetRootNode()const { return _root; }
};

