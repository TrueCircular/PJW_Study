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
			cout << "===================올바른 숫자를 입력해주세요.===================" << endl;
			cout << "===============아무 키나 누르면 처음으로 돌아갑니다==============" << endl;
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
	cout << "=======================성적 관리 시스템==========================" << endl;
	cout << "=================================================================" << endl;
	cout << "1.전체보기 2.검색하기 3.추가하기 4.삭제하기 " << endl;
	cout << "=================================================================" << endl;
	cout << "5.저장하기 6.불러오기 7.나가기" << endl;
	cout << "=================================================================" << endl;
	cout << "숫자를 입력하세요(1~7) : ";
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

	wcout << "= 번호 : " << temp._index << " 학년 : " << temp._grade << " 이름 : " << temp._name <<
		" 국어 : " << temp._kor << " 영어 : " << temp._eng << " 수학 : " << temp._math <<
		" 총점 : " << temp._total << " 평균 : " << temp._average << " =" << endl;
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
		cout << "(1)번호 순 정렬 (2)학년 순 정렬 (3)국어점수 순 정렬 (4)수학점수 순 정렬" << endl;
		cout << "(5)영어점수 순 정렬 (6)총점 순 정렬 (7)평균 순 정렬 (8)나가기" << endl;
		cout << "=======================================================================" << endl;
		cout << "번호를 입력 하세요(1~8) :";
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
	cout << "===========================학생 명부=============================" << endl;
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
