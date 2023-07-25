#pragma once
#include"../QNode/QNode.h"

struct SpaceData
{
	TPoint3 pos;
	TPoint3 surf;

	SpaceData& operator=(SpaceData& data)
	{
		pos = data.pos;
		surf = data.surf;

		return *this;
	}
};

class QTree
{
private:
	QNode*			_root;
	queue<QNode*>	_queue;
	int				_indexCounter = 0;
	vector<QNode*>	_nodeList;
	SpaceData		_sData;
	bool			_isDataSet = false;
private:
	QNode*	CreateNode(QNode* parent, SpaceData data);
	void	Build(QNode* node);
	void	AddNodeToTree(QNode* parent, SpaceData data);
	void	PrintNode(QNode* node);
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
	void	BuildTree();
	void	AddObject(E_ObjectType eType);
	QNode*	FindNode(QObject* fObj);
public:
	void	PreOrder();
	void	LevelOrder();
public:
	QNode*	GetRootNode()const { return _root; }
	void	SetSpaceData(SpaceData data) { _sData = data; }
};

