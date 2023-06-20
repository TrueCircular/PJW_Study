#include <iostream>
#include "SystemState.h"
#include "../gradeSystem/GradeSystem.h"


bool MainState::Run(GradeSystem* system)
{
	if (_isIn == false)
		std::system("cls");

	_isIn = true;

	Print();

	int sNum = 0;

	cin >> sNum;

	if (!cin)
	{
		cin.clear();
		cin.ignore(INT_MAX, '\n');
	}

	switch (sNum)
	{
	case 1:
	{
		system->SetState(E_SysState::SYSTEM_VIEW);
		break;
	}
	case 2:
	{
		system->SetState(E_SysState::SYSTEM_FIND);
		break;
	}
	case 3:
	{
		system->SetState(E_SysState::SYSTEM_ADD);
		break;
	}
	case 4:
	{
		system->SetState(E_SysState::SYSTEM_DELETE);
		break;
	}
	case 5:
	{
		system->SetState(E_SysState::SYSTEM_LOAD);
		break;
	}
	case 6:
	{
		system->SetState(E_SysState::SYSTEM_SAVE);
		break;
	}
	case 7:
	{
		system->SetState(E_SysState::SYSTEM_EXIT);
		break;
	}
	default:
	{
		std::system("cls");
		cout << endl;
		cout << "===================�ùٸ� ���ڸ� �Է����ּ���.===================" << endl;
		cout << endl;
		break;
	}
	}

	return true;
}

void MainState::Print()
{
	cout << "=================================================================" << endl;
	cout << "=======================���� ���� �ý���==========================" << endl;
	cout << "=================================================================" << endl;
	cout << "1.��ü���� 2.�˻��ϱ� 3.�߰��ϱ� 4.�����ϱ� " << endl;
	cout << "=================================================================" << endl;
	cout << "5.�����ϱ� 6.�ҷ����� 7.������" << endl;
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
