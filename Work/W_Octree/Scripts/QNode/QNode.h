#pragma once
#include "../QObject/QObject.h"
class QNode
{
public:
	int					_index = -1;
	int					_depth = 0;
	TRect				_rect;
	TBox				_box;
	QNode*				_parent = nullptr;
	vector<QNode*>		_child;
	vector<QObject*>	_staticObj;
	vector<QObject*>	_dynamicObj;
public:
	QNode(){}
	QNode(int idex) { _index = idex; }
	QNode(TPoint3& pos, TPoint3& surf);
	virtual ~QNode()
	{
		for (int i = 0; i < _child.size(); i++)
		{
			delete _child[i];
			_child[i] = nullptr;
		}
	}
public:
	void SetParent(QNode* parent);
};

