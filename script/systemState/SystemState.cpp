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
			cout << "================== ¿Ã¹Ù¸¥ ¼ýÀÚ¸¦ ÀÔ·ÂÇØÁÖ¼¼¿ä. ==================" << endl;
			cout << "============== ¾Æ¹« Å°³ª ´©¸£¸é Ã³À½À¸·Î µ¹¾Æ°©´Ï´Ù =============" << endl;
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
	cout << "====================== ÇÐ»ý °ü¸® ½Ã½ºÅÛ =========================" << endl;
	cout << "=================================================================" << endl;
	cout << "1.ÀüÃ¼º¸±â 2.°Ë»öÇÏ±â 3.Ãß°¡ÇÏ±â 4.»èÁ¦ÇÏ±â " << endl;
	cout << "=================================================================" << endl;
	cout << "5.ÀúÀåÇÏ±â 6.ºÒ·¯¿À±â 7.³ª°¡±â" << endl;
	cout << "=================================================================" << endl;
	cout << "¼ýÀÚ¸¦ ÀÔ·ÂÇÏ¼¼¿ä(1~7) : ";
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
	cout << "| ÆÄÀÏ ÀúÀå ¹æ½Ä ¼±ÅÃ | (1)ÃÖ±Ù ÀúÀå ÆÄÀÏ (2)»õ·Î¿î ÆÄÀÏ :";
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

		cout << "| ÆÄÀÏ ÀúÀå Çü½Ä ¼±ÅÃ | (1)BIN (2)TXT :";
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
			cout << "============== ¾Æ¹« Å°³ª ´©¸£¸é Ã³À½À¸·Î µ¹¾Æ°©´Ï´Ù =============" << endl;
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
			cout << "============== ¾Æ¹« Å°³ª ´©¸£¸é Ã³À½À¸·Î µ¹¾Æ°©´Ï´Ù =============" << endl;
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
			cout << "================== ¿Ã¹Ù¸¥ ¼ýÀÚ¸¦ ÀÔ·ÂÇØÁÖ¼¼¿ä. ==================" << endl;
			cout << "============== ¾Æ¹« Å°³ª ´©¸£¸é Ã³À½À¸·Î µ¹¾Æ°©´Ï´Ù =============" << endl;
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
		cout << "| ÆÄÀÏ ÀÌ¸§ ÀÛ¼º :";
		cin >> fName;
		cout << "=================================================================" << endl;
		cout << "| ÆÄÀÏ ÀúÀå Çü½Ä ¼±ÅÃ | (1)BIN (2)TXT :";
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
			cout << "============== ¾Æ¹« Å°³ª ´©¸£¸é Ã³À½À¸·Î µ¹¾Æ°©´Ï´Ù =============" << endl;
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
			cout << "============== ¾Æ¹« Å°³ª ´©¸£¸é Ã³À½À¸·Î µ¹¾Æ°©´Ï´Ù =============" << endl;
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
			cout << "================== ¿Ã¹Ù¸¥ ¼ýÀÚ¸¦ ÀÔ·ÂÇØÁÖ¼¼¿ä. ==================" << endl;
			cout << "============== ¾Æ¹« Å°³ª ´©¸£¸é Ã³À½À¸·Î µ¹¾Æ°©´Ï´Ù =============" << endl;
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
		cout << "================== ¿Ã¹Ù¸¥ ¼ýÀÚ¸¦ ÀÔ·ÂÇØÁÖ¼¼¿ä. ==================" << endl;
		cout << "============== ¾Æ¹« Å°³ª ´©¸£¸é Ã³À½À¸·Î µ¹¾Æ°©´Ï´Ù =============" << endl;
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
		cout << "ÀúÀå µÈ ¼¼ÀÌºê ÆÄÀÏÀÌ ¾ø½À´Ï´Ù." << endl;
	}
	cout << "===================================== ÆÄÀÏ ¸ñ·Ï ======================================" << endl;
	do
	{
		cout << _fd.name << endl;
		cout << "======================================================================================" << endl;
	} while (_findnext(_handle, &_fd) == 0);

	_findclose(_handle);
}

void LoadState::ErrorPrint()
{
	cout << "================== ¿Ã¹Ù¸¥ ¼ýÀÚ¸¦ ÀÔ·ÂÇØÁÖ¼¼¿ä. ==================" << endl;
	cout << "============== ¾Æ¹« Å°³ª ´©¸£¸é Ã³À½À¸·Î µ¹¾Æ°©´Ï´Ù =============" << endl;
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
		cout << "| ¸Þ´º ¼±ÅÃ | (1)ÆÄÀÏ ¸ñ·Ï Ãâ·Â (2) ³ª°¡±â :";
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

			cout << "| Ãâ·Â ÇÒ ÆÄÀÏ ¸ñ·Ï È®ÀåÀÚ ¼±ÅÃ | (1)TXT (2)BIN :";
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
				cout << "| ÆÄÀÏ ÀÌ¸§ ÀÔ·Â | :";
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
				cout << "| ÆÄÀÏ ÀÌ¸§ ÀÔ·Â | :";
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
	cout << "====================================== ºÒ·¯¿À±â ======================================" << endl;
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

void AddState::ErrorPrint()
{
	cout << "============================= ¿Ã¹Ù¸¥ ¼ýÀÚ¸¦ ÀÔ·ÂÇØÁÖ¼¼¿ä. ============================" << endl;
	cout << "========================= ¾Æ¹« Å°³ª ´©¸£¸é Ã³À½À¸·Î µ¹¾Æ°©´Ï´Ù =======================" << endl;
	cout << endl;
	_isIn = false;
	_getche();
}

void AddState::AddStudentInfo(GradeSystem* system)
{
	sData sTemp;

	try
	{
		cout << "| ÇÐ»ý Á¤º¸ ÀÔ·Â | ¹øÈ£(1~1000) :";
		cin >> sTemp._index;
		cout << "======================================================================================" << endl;
		if ((sTemp._index <= 0 || sTemp._index > 1000) ||
			!OverlapCheck(system, sTemp._index))
			throw sTemp._index;

		cout << "| ÇÐ»ý Á¤º¸ ÀÔ·Â | ÇÐ³â(1~10) :";
		cin >> sTemp._grade;
		cout << "======================================================================================" << endl;
		if (sTemp._grade <= 0 || sTemp._grade > 10)
			throw sTemp._grade;

		cout << "| ÇÐ»ý Á¤º¸ ÀÔ·Â | ÀÌ¸§ :";
		wcin >> sTemp._name;
		cout << "======================================================================================" << endl;
		for (wchar_t ch : sTemp._name)
		{
			if (!((ch >= L'a' && ch <= L'z') || 
				(ch >= L'A' && ch <= L'Z') || 
				(ch >= L'°¡' && ch <= L'ÆR'))) 
			{
				throw sTemp._name;
			}
		}


		cout << "| ÇÐ»ý Á¤º¸ ÀÔ·Â | ±¹¾î Á¡¼ö(1~100) :";
		cin >> sTemp._kor;
		cout << "======================================================================================" << endl;
		if (sTemp._kor <= 0 || sTemp._kor > 100)
			throw sTemp._kor;

		cout << "| ÇÐ»ý Á¤º¸ ÀÔ·Â | ¿µ¾î Á¡¼ö(1~100) :";
		cin >> sTemp._eng;
		cout << "======================================================================================" << endl;
		if (sTemp._eng <= 0 || sTemp._eng > 100)
			throw sTemp._eng;

		cout << "| ÇÐ»ý Á¤º¸ ÀÔ·Â | ¼öÇÐ Á¡¼ö(1~100) :";
		cin >> sTemp._math;
		cout << "======================================================================================" << endl;
		if (sTemp._math <= 0 || sTemp._math > 100)
			throw sTemp._math;
	}
	catch (int number)
	{
		ErrorPrint();
		return;
	}
	catch (wstring st)
	{
		ErrorPrint();
		return;
	}

	sTemp._total = sTemp._kor + sTemp._eng + sTemp._math;
	sTemp._average = trunc((sTemp._total / 3.f));
	
	system->GetDataBase()->AddInfo(sTemp);
	cout << "| ¹øÈ£ :" << sTemp._index << "¹ø ÇÐ³â :" << sTemp._grade << "ÇÐ³â ÀÌ¸§ :";
	wcout << sTemp._name;
	cout << " ±¹¾î :" << sTemp._kor << "Á¡ ¿µ¾î :" << sTemp._eng << "Á¡ ¼öÇÐ :" << sTemp._math <<
		"Á¡ ÃÑÁ¡ :" << sTemp._total << "Á¡ Æò±Õ :" << sTemp._average << " <Ãß°¡ ¿Ï·á>" << endl;
	cout << "======================================================================================" << endl;
	_getche();
}

bool AddState::OverlapCheck(GradeSystem* system, int number)
{
	DynamicArray<Info<sData>*> buffer;

	for (int i = 0; i < system->GetDataBase()->size(); i++)
	{
		buffer.push_back(system->GetDataBase()->SearchInfoForIndex(i));
	}

	for (Info<sData> i : buffer)
	{
		if (i._data._index == number)
		{
			cout << "Áßº¹µÈ ¹øÈ£ ÀÔ´Ï´Ù." << endl;
			cout << "======================================================================================" << endl;
			return false;
		}
	}

	return true;
}


bool AddState::Run(GradeSystem* system)
{
	if (!_isIn)
	{
		std::system("cls");

		_isIn = true;

		Print();
	}
	else
	{
		int num = 0;
		cout << "| ¸Þ´º | (1)ÇÐ»ý Á¤º¸ Ãß°¡ (2)³ª°¡±â :";
		cin >> num;
		cout << "======================================================================================" << endl;
		if (!cin)
		{
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}

		switch (num)
		{
		case 1:
		{
			AddStudentInfo(system);
			_isIn = false;
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

void AddState::Print()
{
	cout << "======================================================================================" << endl;
	cout << "================================= ÇÐ»ý Á¤º¸ Ãß°¡ =====================================" << endl;
	cout << "======================================================================================" << endl;
}

void ViewState::PrintStudentInfo(Info<sData>* data)
{
	if (data == nullptr)
		return;

	sData temp = data->_data;

	wcout << L"== ¹øÈ£:" << temp._index << L"¹ø ÇÐ³â:" << temp._grade << L"ÇÐ³â ÀÌ¸§:" << temp._name <<
		L" ±¹¾î:" << temp._kor << L"Á¡ ¿µ¾î:" << temp._eng << L"Á¡ ¼öÇÐ:" << temp._math <<
		L"Á¡ ÃÑÁ¡:" << temp._total << L"Á¡ Æò±Õ:" << temp._average << endl;
	cout << "======================================================================================" << endl;
}

void ViewState::PrintSorting(GradeSystem* system, E_SortingType sType)
{
	int num2 = 0;

	cout << "======================================================================================" << endl;
	cout << "Á¤·Ä ¹æ½ÄÀ» ¼±ÅÃÇÏ¼¼¿ä. (1)¿À¸§Â÷ ¼ø (2)³»¸²Â÷ ¼ø :";
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
		cout << "============================= ¿Ã¹Ù¸¥ ¼ýÀÚ¸¦ ÀÔ·ÂÇØÁÖ¼¼¿ä. ============================" << endl;
		cout << "========================= ¾Æ¹« Å°³ª ´©¸£¸é Ã³À½À¸·Î µ¹¾Æ°©´Ï´Ù =======================" << endl;
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
		cout << "========(1)¹øÈ£ ¼ø Á¤·Ä (2)ÇÐ³â ¼ø Á¤·Ä (3)±¹¾îÁ¡¼ö ¼ø Á¤·Ä (4)¿µ¾îÁ¡¼ö ¼ø Á¤·Ä=======" << endl;
		cout << "========(5)¼öÇÐÁ¡¼ö ¼ø Á¤·Ä (6)ÃÑÁ¡ ¼ø Á¤·Ä (7)Æò±Õ ¼ø Á¤·Ä (8)³ª°¡±â          =======" << endl;
		cout << "======================================================================================" << endl;
		cout << "¹øÈ£¸¦ ÀÔ·Â ÇÏ¼¼¿ä(1~8) :";
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
			cout << "============================= ¿Ã¹Ù¸¥ ¼ýÀÚ¸¦ ÀÔ·ÂÇØÁÖ¼¼¿ä. ============================" << endl;
			cout << "========================= ¾Æ¹« Å°³ª ´©¸£¸é Ã³À½À¸·Î µ¹¾Æ°©´Ï´Ù =======================" << endl;
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
	cout << "===================================== ÇÐ»ý ¸íºÎ ======================================" << endl;
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
