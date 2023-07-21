#include "QNode.h"

void QNode::SetParent(QNode* parent)
{
	if (parent == nullptr)
		return;

	_parent = parent;
	_depth = parent->_depth + 1;
}
