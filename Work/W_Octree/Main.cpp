#pragma once
#include"Myheaders.h"

void StaticObjSet(QTree& tree, vector<QObject*>& StaticObjList)
{
	int width = tree.GetRootNode()->_box.m_fWidth;
	int height = tree.GetRootNode()->_box.m_fHeight;
	int depth = tree.GetRootNode()->_box.m_fDepth;

	int randCount = 0;

	for (int i = 0; i < 20; i++)
	{
		QObject* sObject = new QStaticObject();

		randCount = rand() % 2;

		switch (randCount)
		{
		case 0:
			sObject->_name = L"����";
			break;
		case 1:
			sObject->_name = L"��";
			break;
		}
		sObject->_name += L"[";
		sObject->_name += to_wstring(i+1);
		sObject->_name += L"]";

		sObject->_position = { (float)(rand() % width) + 1,
							   (float)(rand() % height) + 1,
							   (float)(rand() % depth) + 1 };
		TPoint3 sPoint = { 10.f, 10.f, 10.f };
		sObject->SetObject(sObject->_position, sPoint);

		tree.AddObject(E_ObjectType::OBJECT_STATIC, sObject);
		StaticObjList.push_back(sObject);
	}

	//QObject* test = new QStaticObject();
	//test->_name = L"�׽�Ʈ";
	//test->_position = { 350,300,300 };
	//TPoint3 tpo = { 10.f, 10.f, 10.f };
	//test->SetObject(test->_position, tpo);
	//tree.AddObject(E_ObjectType::OBJECT_STATIC, test);
	//StaticObjList.push_back(test);
}
void ObjectMove(int a, QObject* user) {
	switch (a)
	{
	case 1:
	{
		user->Move(E_MoveType::MOVE_FORWARD, 1.f);
		break;
	}
	case 2:
	{
		user->Move(E_MoveType::MOVE_BACK, 1.f);
		break;
	}
	case 3:
	{
		user->Move(E_MoveType::MOVE_UP, 1.f);
		break;
	}
	case 4:
	{
		user->Move(E_MoveType::MOVE_DOWN, 1.f);
		break;
	}
	case 5:
	{
		user->Move(E_MoveType::MOVE_LEFT, 1.f);
		break;
	}
	case 6:
	{
		user->Move(E_MoveType::MOVE_RIGHT, 1.f);
		break;
	}
	default:
		break;
	}
}

int main()
{
	std::locale::global(std::locale("Korean"));

	vector<QObject*> StaticObjList;
	QObject* user = new QDynamicObject();

	QTree ocTree;
	SpaceData tData;
	tData.pos = { 0,0,0 };
	tData.surf = { 600.f,600.f,600.f };
	ocTree.SetSpaceData(tData);
	ocTree.Init();
	StaticObjSet(ocTree, StaticObjList);

	SpaceData pData;
	pData.pos = { 300.f,300.f,300.f };
	pData.surf = { 10.f,10.f,10.f };
	user->SetObject(pData.pos, pData.surf);
	ocTree.AddObject(E_ObjectType::OBJECT_DYNAMIC, user);

	TTimer* mTimer = Util::GetInstance()->GetTimer();
	mTimer->Init();
	int sel = 0;

	while (1)
	{
		system("cls");

		mTimer->Frame();

		ocTree.PreFrame();
		ocTree.AddObject(E_ObjectType::OBJECT_DYNAMIC, user);
		ocTree.Frame();

		cout << "====== ���� ������Ʈ ======" << endl;
		for (int i = 0; i < StaticObjList.size(); i++)
		{
			wcout << L"=" << StaticObjList[i]->_name <<
				L" X:" << StaticObjList[i]->_position.x <<
				L" Y:" << StaticObjList[i]->_position.y <<
				L" Z:" << StaticObjList[i]->_position.z << endl;
		}

		cout << "===========================" << endl;
		cout << "====== ���� ������Ʈ ======" << endl;
		wcout << L"=" << user->_name <<
			L" X:" << user->_box.v.x <<
			L" Y:" << user->_box.v.y <<
			L" Z:" << user->_box.v.z << endl;
		cout << "===========================" << endl;
		cout << "���� ������Ʈ �̵� : [1]�� [2]�� [3]�� [4]�Ʒ� [5]���� [6]������ :";
		cin >> sel;
		ObjectMove(sel, user);
		cout << "===========================" << endl;
		_getche();

		ocTree.PostFrame();
	}
	mTimer->Release();

	return 0;
}