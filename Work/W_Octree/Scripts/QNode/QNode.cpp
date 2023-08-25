#include "QNode.h"

QNode::QNode(TPoint3& pos, TPoint3& surf)
{
	this->_box.Set(pos, surf);
}

void QNode::SetParent(QNode* parent)
{
	if (parent == nullptr)
		return;

	_parent = parent;
	_depth = parent->_depth + 1;
}
