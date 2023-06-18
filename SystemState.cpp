#include <iostream>
#include "SystemState.h"
#include "GradeSystem.h"


bool MainState::Run(GradeSystem* system)
{
	if (_isIn == false)
		std::system("cls");

	_isIn = true;

	Print();

	int sNum = 0;

	cin >> sNum;

	switch (sNum)
	{
	case 1:
	{
		SystemState* temp = new ViewState();
		system->GetAddressList()->push_back(&temp);
		system->SetState(temp);
		break;
	}
	case 2:
	{
		SystemState* temp = new AddState();
		system->GetAddressList()->push_back(&temp);
		system->SetState(temp);
		break;
	}
	case 3:
	{
		SystemState* temp = new DelState();
		system->GetAddressList()->push_back(&temp);
		system->SetState(temp);
		break;
	}
	case 4:
	{

	}
	case 5:
	{
		SystemState* temp = new SaveState();
		system->GetAddressList()->push_back(&temp);
		system->SetState(temp);
		break;
	}
	case 6:
	{
		SystemState* temp = new LoadState();
		system->GetAddressList()->push_back(&temp);
		system->SetState(temp);
		break;
	}
	case 7:
	{
		SystemState* temp = new ExitState();
		system->GetAddressList()->push_back(&temp);
		system->SetState(temp);
		break;
	}
	default:
	{
		std::system("cls");
		cout << endl;
		cout << "===================�ùٸ� ���ڸ� �Է����ּ���.===================" << endl;
		cout << endl;
	}
	}

	return true;
}

void MainState::Print()
{
	cout << "=================================================================" << endl;
	cout << "=======================���� ���� �ý���==========================" << endl;
	cout << "=================================================================" << endl;
	cout << "1.��ü���� 2.�˻��ϱ� 3.�߰��ϱ� 4.�����ϱ� 5.�����ϱ� 6.�ҷ�����" << endl;
	cout << "=================================================================" << endl;
	cout << "7.������" << endl;
	cout << "=================================================================" << endl;
	cout << "���ڸ� �Է��ϼ���(1~7) : ";
}

bool ExitState::Run(GradeSystem* system)
{
	return false;
}

void ExitState::Print()
{
}

bool SaveState::Run(GradeSystem* system)
{
	return false;
}

void SaveState::Print()
{
}

bool LoadState::Run(GradeSystem* system)
{
	return false;
}

void LoadState::Print()
{
}

bool DelState::Run(GradeSystem* system)
{
	return false;
}

void DelState::Print()
{
}

AddState::AddState()
{
}

AddState::~AddState()
{
}

bool AddState::Run(GradeSystem* system)
{
	return false;
}

void AddState::Print()
{
}

ViewState::ViewState()
{
	_isIn = false;
}

ViewState::~ViewState()
{
}

bool ViewState::Run(GradeSystem* system)
{
	return false;
}

void ViewState::Print()
{
}

bool SearchState::Run(GradeSystem* system)
{
	return false;
}

void SearchState::Print()
{
}
