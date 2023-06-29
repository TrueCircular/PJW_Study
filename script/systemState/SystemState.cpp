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
			system->SetState(E_SysState::SYSTEM_SAVE);
			_isIn = false;
			break;
		}
		case 6:
		{
			system->SetState(E_SysState::SYSTEM_LOAD);
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
			cout << "================== 올바른 숫자를 입력해주세요. ==================" << endl;
			cout << "============== 아무 키나 누르면 처음으로 돌아갑니다 =============" << endl;
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
	cout << "====================== 학생 관리 시스템 =========================" << endl;
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
	int selNum = 0;

	cout << "=================================================================" << endl;
	cout << "| 파일 저장 방식 선택 | (1)최근 저장 파일 (2)새로운 파일 :";
	cin >> selNum;
	cout << "=================================================================" << endl;
	if (!cin)
	{
		cin.clear();
		cin.ignore(INT_MAX, '\n');
	}
	switch (selNum)
	{
	case 1:
	{
		int num = 0;

		cout << "| 파일 저장 형식 선택 | (1)BIN (2)TXT :";
		cin >> num;
		cout << "=================================================================" << endl;
		if (!cin)
		{
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
		switch (num)
		{
		case 1:
		{
			cout << "============== 아무 키나 누르면 처음으로 돌아갑니다 =============" << endl;
			cout << "=================================================================" << endl;
			system->SaveFile();
			if (_getche())
			{
				system->SetState(E_SysState::SYSTEM_MAIN);
			}
			break;
		}
		case 2:
		{
			cout << "============== 아무 키나 누르면 처음으로 돌아갑니다 =============" << endl;
			cout << "=================================================================" << endl;
			system->SaveFile("", E_SaveMode::SAVE_PREV, E_SaveType::SAVE_TXT);
			if (_getche())
			{
				system->SetState(E_SysState::SYSTEM_MAIN);
			}
			break;
		}
		default:
		{
			cout << "================== 올바른 숫자를 입력해주세요. ==================" << endl;
			cout << "============== 아무 키나 누르면 처음으로 돌아갑니다 =============" << endl;
			cout << endl;
			if (_getche())
				_isIn = false;
			break;
		}
		}
		break;
	}
	case 2:
	{
		int num = 0;
		string fName;
		cout << "| 파일 이름 작성 :";
		cin >> fName;
		cout << "=================================================================" << endl;
		cout << "| 파일 저장 형식 선택 | (1)BIN (2)TXT :";
		cin >> num;
		if (!cin)
		{
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
		switch (num)
		{
		case 1:
		{
			cout << "=================================================================" << endl;
			cout << "============== 아무 키나 누르면 처음으로 돌아갑니다 =============" << endl;
			cout << "=================================================================" << endl;
			system->SaveFile(fName.c_str(), E_SaveMode::SAVE_NEW, E_SaveType::SAVE_BIN);

			if (_getche())
			{
				system->SetState(E_SysState::SYSTEM_MAIN);
			}
			break;
		}
		case 2:
		{
			cout << "=================================================================" << endl;
			cout << "============== 아무 키나 누르면 처음으로 돌아갑니다 =============" << endl;
			cout << "=================================================================" << endl;
			system->SaveFile(fName.c_str(), E_SaveMode::SAVE_NEW, E_SaveType::SAVE_TXT);
			if (_getche())
			{
				system->SetState(E_SysState::SYSTEM_MAIN);
			}
			break;
		}
		default:
		{
			cout << "================== 올바른 숫자를 입력해주세요. ==================" << endl;
			cout << "============== 아무 키나 누르면 처음으로 돌아갑니다 =============" << endl;
			cout << endl;
			if (_getche())
				_isIn = false;
			break;
		}
		}
		break;
	}
	default:
	{
		cout << "================== 올바른 숫자를 입력해주세요. ==================" << endl;
		cout << "============== 아무 키나 누르면 처음으로 돌아갑니다 =============" << endl;
		cout << endl;
		if (_getche())
			_isIn = false;

		break;
	}
	}
	

	return true;
}

void SaveState::Print()
{
}

void LoadState::PrintSaveFileList(string path)
{
	std::filesystem::path _abPath;

	_abPath = path;
	_abPath = std::filesystem::absolute(_abPath);

	if ((_handle = _findfirst(_abPath.string().c_str(), &_fd)) == -1L)
	{
		cout << "저장 된 세이브 파일이 없습니다." << endl;
	}
	cout << "===================================== 파일 목록 ======================================" << endl;
	do
	{
		cout << _fd.name << endl;
		cout << "======================================================================================" << endl;
	} while (_findnext(_handle, &_fd) == 0);

	_findclose(_handle);
}

void LoadState::ErrorPrint()
{
	cout << "================== 올바른 숫자를 입력해주세요. ==================" << endl;
	cout << "============== 아무 키나 누르면 처음으로 돌아갑니다 =============" << endl;
	cout << endl;
	_isIn = false;
	_getche();
}

LoadState::LoadState()
{
	_rePath = MYLOCALPATH_SAVE;

}

LoadState::~LoadState()
{
}

bool LoadState::Run(GradeSystem* system)
{
	if (!_isIn)
	{
		std::system("cls");
		_isIn = true;

		Print();
	}
	else
	{
		int tNum = 0;
		cout << "| 메뉴 선택 | (1)파일 목록 출력 (2) 나가기 :";
		cin >> tNum;
		cout << "======================================================================================" << endl;
		if (!cin)
		{
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
		switch (tNum)
		{
		case 1:
		{
			string fName;
			int selNum = 0;

			cout << "| 출력 할 파일 목록 확장자 선택 | (1)TXT (2)BIN :";
			cin >> selNum;
			cout << "======================================================================================" << endl;

			if (!cin)
			{
				cin.clear();
				cin.ignore(INT_MAX, '\n');
			}
			switch (selNum)
			{
			case 1:
			{
				_rePath = MYLOCALPATH_SAVE;
				_rePath.append("*.txt");
				PrintSaveFileList(_rePath);

				string fName;
				cout << "| 파일 이름 입력 | :";
				cin >> fName;
				cout << "======================================================================================" << endl;
				system->GetDataBase()->AllDelete();
				system->LoadFile(fName.c_str(), E_LoadMode::LOAD_NEW, E_LoadType::LOAD_TXT);
				cout << "======================================================================================" << endl;
				break;
			}
			case 2:
			{
				_rePath = MYLOCALPATH_SAVE;
				_rePath.append("*.bin");
				PrintSaveFileList(_rePath);

				string fName;
				cout << "| 파일 이름 입력 | :";
				cin >> fName;
				cout << "======================================================================================" << endl;
				system->GetDataBase()->AllDelete();
				system->LoadFile(fName.c_str(), E_LoadMode::LOAD_NEW, E_LoadType::LOAD_BIN);
				cout << "======================================================================================" << endl;
				break;
			}
			default:
			{
				ErrorPrint();
				return true;
			}
			}

			break;
		}
		case 2:
		{
			_isIn = false;
			system->SetState(E_SysState::SYSTEM_MAIN);
			break;
		}
		default:
		{
			ErrorPrint();
			return true;
		}
		}
	}
	return true;
}

void LoadState::Print()
{
	cout << "======================================================================================" << endl;
	cout << "====================================== 불러오기 ======================================" << endl;
	cout << "======================================================================================" << endl;
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

	wcout << L"== 번호:" << temp._index << L"번 학년:" << temp._grade << L"학년 이름:" << temp._name <<
		L" 국어:" << temp._kor << L"점 영어:" << temp._eng << L"점 수학:" << temp._math <<
		L"점 총점:" << temp._total << L"점 평균:" << temp._average << L" ==" << endl;
	cout << "======================================================================================" << endl;
}

void ViewState::PrintSorting(GradeSystem* system, E_SortingType sType)
{
	int num2 = 0;

	cout << "======================================================================================" << endl;
	cout << "정렬 방식을 선택하세요. (1)오름차 순 (2)내림차 순 :";
	cin >> num2;

	if (!cin)
	{
		cin.clear();
		cin.ignore(INT_MAX, '\n');
	}

	if (num2 == 1)
	{
		system->SortingForDatabase(E_Sort::SORT_HIGH, sType);
		_isIn = false;
	}
	else if (num2 == 2)
	{
		system->SortingForDatabase(E_Sort::SORT_LOW, sType);
		_isIn = false;
	}
	else
	{
		cout << "============================= 올바른 숫자를 입력해주세요. ============================" << endl;
		cout << "========================= 아무 키나 누르면 처음으로 돌아갑니다 =======================" << endl;
		cout << endl;

		if (_getche())
			_isIn = false;
	}
}

ViewState::ViewState()
{
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
		cout << "======================================================================================" << endl;
		cout << "========(1)번호 순 정렬 (2)학년 순 정렬 (3)국어점수 순 정렬 (4)영어점수 순 정렬=======" << endl;
		cout << "========(5)수학점수 순 정렬 (6)총점 순 정렬 (7)평균 순 정렬 (8)나가기          =======" << endl;
		cout << "======================================================================================" << endl;
		cout << "번호를 입력 하세요(1~8) :";
	}
	else
	{
		int num = 0;

		cin >> num;

		if (!cin)
		{
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}

		switch (num)
		{
		case 1:
		{
			PrintSorting(system, E_SortingType::SORTING_NUMBER);
			break;
		}
		case 2:
		{
			PrintSorting(system, E_SortingType::SORTING_GRADE);
			break;
		}
		case 3:
		{
			PrintSorting(system, E_SortingType::SORINTG_KOR);
			break;
		}
		case 4:
		{
			PrintSorting(system, E_SortingType::SORTING_ENG);
			break;
		}
		case 5:
		{
			PrintSorting(system, E_SortingType::SORTING_MATH);
			break;
		}
		case 6:
		{
			PrintSorting(system, E_SortingType::SORTING_TOTAL);
			break;
		}
		case 7:
		{
			PrintSorting(system, E_SortingType::SORTING_AVERAGE);
			break;
		}
		case 8:
		{
			system->SortingForDatabase(E_Sort::SORT_HIGH, E_SortingType::SORTING_NUMBER);
			system->SetState(E_SysState::SYSTEM_MAIN);
			_isIn = false;
			break;
		}
		default:
		{
			cout << "============================= 올바른 숫자를 입력해주세요. ============================" << endl;
			cout << "========================= 아무 키나 누르면 처음으로 돌아갑니다 =======================" << endl;
			cout << endl;

			if (_getche())
				_isIn = false;
			break;
		}
		}
	}

	return true;
}

void ViewState::Print()
{
	cout << "======================================================================================" << endl;
	cout << "===================================== 학생 명부 ======================================" << endl;
	cout << "======================================================================================" << endl;
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
