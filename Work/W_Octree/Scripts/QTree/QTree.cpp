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
	if (node->_depth > 2)
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
	return true;
}

bool QTree::Frame()
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

	return true;
}

void QTree::BuildTree()
{
	_root = CreateNode(nullptr, _sData);
	Build(_root);
}

void QTree::AddObject(E_ObjectType eType)
{
}

QNode* QTree::FindNode(QObject* fObj)
{
	return nullptr;
}

void QTree::PreOrder()
{
}

void QTree::LevelOrder()
{
}
