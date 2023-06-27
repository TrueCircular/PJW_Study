#include <iostream>
#include <conio.h>
#include "SystemState.h"
#include "../gradeSystem/GradeSystem.h"


MainState::MainState()
{
}

MainState::~MainState()
{
}

bool MainState::Run(GradeSystem* system)
{
	if (_isIn == false)
	{
		std::system("cls");

		_isIn = true;

		Print();
	}
	else
	{
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
			_isIn = false;
			break;
		}
		case 2:
		{
			system->SetState(E_SysState::SYSTEM_FIND);
			_isIn = false;
			break;
		}
		case 3:
		{
			system->SetState(E_SysState::SYSTEM_ADD);
			_isIn = false;
			break;
		}
		case 4:
		{
			system->SetState(E_SysState::SYSTEM_DELETE);
			_isIn = false;
			break;
		}
		case 5:
		{
			system->SetState(E_SysState::SYSTEM_LOAD);
			_isIn = false;
			break;
		}
		case 6:
		{
			system->SetState(E_SysState::SYSTEM_SAVE);
			_isIn = false;
			break;
		}
		case 7:
		{
			system->SetState(E_SysState::SYSTEM_EXIT);
			_isIn = false;
			break;
		}
		default:
		{
			cout << endl;
			cout << "===================�ùٸ� ���ڸ� �Է����ּ���.===================" << endl;
			cout << "===============�ƹ� Ű�� ������ ó������ ���ư��ϴ�==============" << endl;
			cout << endl;
			if (_getche())
				_isIn = false;

			break;
		}
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

ExitState::ExitState()
{
}

ExitState::~ExitState()
{
}

bool ExitState::Run(GradeSystem* system)
{
	return false;
}

void ExitState::Print()
{
}

SaveState::SaveState()
{
}

SaveState::~SaveState()
{
}

bool SaveState::Run(GradeSystem* system)
{
	

	return false;
}

void SaveState::Print()
{

}

LoadState::LoadState()
{
}

LoadState::~LoadState()
{
}

bool LoadState::Run(GradeSystem* system)
{
	return false;
}

void LoadState::Print()
{
}

DelState::DelState()
{
}

DelState::~DelState()
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

void ViewState::PrintStudentInfo(Info<sData>* data)
{
	if (data == nullptr)
		return;

	sData temp = data->_data;

	wcout << "= ��ȣ : " << temp._index << " �г� : " << temp._grade << " �̸� : " << temp._name <<
		" ���� : " << temp._kor << " ���� : " << temp._eng << " ���� : " << temp._math <<
		" ���� : " << temp._total << " ��� : " << temp._average << " =" << endl;
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
	if (_isIn == false)
	{
		std::system("cls");

		_isIn = true;

		Print();

		for (int i = 0; i < system->GetDataBase()->size(); i++)
		{
			PrintStudentInfo(system->GetDataBase()->SearchInfoForIndex(i));
		}


		cout << "=======================================================================" << endl;
		cout << "(1)��ȣ �� ���� (2)�г� �� ���� (3)�������� �� ���� (4)�������� �� ����" << endl;
		cout << "(5)�������� �� ���� (6)���� �� ���� (7)��� �� ���� (8)������" << endl;
		cout << "=======================================================================" << endl;
		cout << "��ȣ�� �Է� �ϼ���(1~8) :";
	}
	else
	{
		int num = 0;
		cin >> num;

		switch (num)
		{
		case 1:
		{
			break;
		}
		case 2:
		{
			break;
		}
		case 3:
		{
			break;
		}
		case 4:
		{
			break;
		}
		case 5:
		{
			break;
		}
		case 6:
		{
			break;
		}
		case 7:
		{
			break;
		}
		case 8:
		{
			break;
		}
		default:
		{
			break;
		}
		}
	}

	return false;
}

void ViewState::Print()
{
	cout << "=================================================================" << endl;
	cout << "===========================�л� ���=============================" << endl;
	cout << "=================================================================" << endl;
}

SearchState::SearchState()
{
}

SearchState::~SearchState()
{
}

bool SearchState::Run(GradeSystem* system)
{
	return false;
}

void SearchState::Print()
{
}
