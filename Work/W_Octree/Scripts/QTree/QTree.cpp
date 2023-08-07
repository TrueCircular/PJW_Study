#include "QTree.h"

QNode* QTree::CreateNode(QNode* parent, SpaceData data)
{
	QNode* temp = new QNode(_indexCounter++);
	temp->SetParent(parent);
	temp->_box.Set(data.pos, data.surf);
	return temp;
}

void QTree::Build(QNode* node)
{
	if (node->_depth > 1)
		return;

	TPoint3 vTC1 = { node->_box.m_Center.x, node->_box.m_Point[0].y,
				 node->_box.m_Min.z };
	TPoint3 vLC1 = { node->_box.m_Point[0].x, node->_box.m_Center.y,
					node->_box.m_Min.z };
	TPoint3 vTC2 = { node->_box.m_Center.x, node->_box.m_Point[0].y,
					node->_box.m_Center.z };
	TPoint3 vLC2 = { node->_box.m_Point[0].x, node->_box.m_Center.y,
					node->_box.m_Center.z };

	SpaceData nodebox;
	nodebox.surf = node->_box.m_Half;
	//1
	nodebox.pos = node->_box.m_Point[0];
	AddNodeToTree(node, nodebox);
	//2
	nodebox.pos = vTC1;
	AddNodeToTree(node, nodebox);
	//3
	nodebox.pos = node->_box.m_Center;
	nodebox.pos.z = node->_box.m_Min.z;
	AddNodeToTree(node, nodebox);
	//4
	nodebox.pos = vLC1;
	AddNodeToTree(node, nodebox);
	//5
	nodebox.pos = node->_box.m_Point[0];
	nodebox.pos.z = node->_box.m_Center.z;
	AddNodeToTree(node, nodebox);
	//6
	nodebox.pos = vTC2;
	AddNodeToTree(node, nodebox);
	//7
	nodebox.pos = node->_box.m_Center;
	AddNodeToTree(node, nodebox);
	//8
	nodebox.pos = vLC2;
	AddNodeToTree(node, nodebox);

	PrintNode(node);

	for (int i = 0; i < node->_child.size(); i++)
	{
		Build(node->_child[i]);
	}
}

void QTree::AddNodeToTree(QNode* parent, SpaceData data)
{
	QNode* tNode;
	tNode = CreateNode(parent, data);
	parent->_child.push_back(tNode);
	_nodeList.push_back(tNode);
}

void QTree::PrintNode(QNode* node)
{
	cout << "±íÀÌ [" << node->_depth << "]" <<
			"X:" << node->_box.m_fx << 
			" Y:" <<node->_box.m_fy << 
			" Z:" << node->_box.m_fz <<
			" Width:" << node->_box.m_fWidth << 
			" Height:" << node->_box.m_fHeight << 
			" Depth:" << node->_box.m_fDepth << endl;
}

bool QTree::Init()
{
	if (_isDataSet == false)
		return false;

	BuildTree();

	return true;
}

bool QTree::PreFrame()
{
	for (auto n : _dynamicObjNode)
	{
		n->_dynamicObj.clear();
	}


	_dynamicObjNode.clear();
	return true;
}

bool QTree::Frame()
{
	if (_dynamicObjNode.size() > 0 &&
		_staticObjNode.size() > 0)
	{
		QObject* mObj = nullptr;
		for (auto a : _dynamicObjNode)
		{
			mObj = a->_dynamicObj[0];
		}

		if (mObj != nullptr)
		{
			for (auto a : _staticObjNode)
			{
				for (int i = 0; i < a->_staticObj.size(); i++)
				{
					if (mObj->Collision(a->_staticObj[i]->_box))
						break;	
				}
			}
		}

	}
	return true;
}

bool QTree::PostFrame()
{
	return true;
}

bool QTree::Render()
{
	return true;
}

bool QTree::Release()
{
	delete _root;
	_isDataSet = false;

	return true;
}

void QTree::BuildTree()
{
	_root = CreateNode(nullptr, _sData);
	Build(_root);
}

void QTree::AddObject(E_ObjectType eType, QObject* obj)
{
	switch (eType)
	{
	case E_ObjectType::OBJECT_STATIC:
	{
		QNode* toAddNode = FindNode(obj);
		if (toAddNode != nullptr)
		{
			obj->_nodeIndex = toAddNode->_index;
			toAddNode->_staticObj.push_back(obj);
			_staticObjNode.insert(toAddNode);
		}
		break;
	}
	case E_ObjectType::OBJECT_DYNAMIC:
	{
		QNode* toAddNode = FindNode(obj);
		if (toAddNode != nullptr)
		{
			obj->_nodeIndex = toAddNode->_index;
			toAddNode->_dynamicObj.push_back(obj);
			_dynamicObjNode.insert(toAddNode);
		}
		break;
	}
	}

}

QNode* QTree::FindNode(QObject* fObj)
{
	if (_root == nullptr) return nullptr;

	QNode* temp = _root;

	do
	{
		for (int i = 0; i < temp->_child.size(); i++)
		{
			if (temp->_child[i] != nullptr)
			{
				if (Util::GetInstance()->BoxToBox(temp->_child[i]->_box, fObj->_box))
				{
					_queue.push(temp->_child[i]);
					break;
				}
			}
		}
		if (_queue.empty()) break;
		temp = _queue.front();
		_queue.pop();

	} while (temp);

	return temp;
}
