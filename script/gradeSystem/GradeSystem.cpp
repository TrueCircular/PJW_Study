#include "GradeSystem.h"
#include "../systemState/SystemState.h"
//#include "../gradeList/GradeList.h"

void GradeSystem::Init()
{
	std::locale::global(std::locale("Korean"));

	_stateList = new StateList();
	StateInit();
	SetState(E_SysState::SYSTEM_MAIN);

	_dataBase = new GradeList<sData, GradeSystem>();
	_inFile = new wifstream();
	_outFile = new wofstream();
	_sortFun = &GradeSystem::InsertionSortingHigh;

	sData t1;
	t1._index = 0;
	t1._name = L"김철수";
	t1._grade = 1;
	t1._kor = 50;
	t1._eng = 40;
	t1._math = 80;
	t1._total = t1._kor + t1._math + t1._eng;
	t1._average = t1._total / 3.f;
	t1._average = truncf(t1._average);
	_dataBase->AddInfo(t1);

	sData t2;
	t2._index = 1;
	t2._name = L"김명수";
	t2._grade = 1;
	t2._kor = 60;
	t2._eng = 30;
	t2._math = 50;
	t2._total = t2._kor + t2._math + t2._eng;
	t2._average = t2._total / 3.f;
	t2._average = truncf(t2._average);
	_dataBase->AddInfo(t2);

	sData t3;
	t3._index = 2;
	t3._name = L"김영희";
	t3._grade = 1;
	t3._kor = 80;
	t3._eng = 90;
	t3._math = 90;
	t3._total = t3._kor + t3._math + t3._eng;
	t3._average = t3._total / 3.f;
	t3._average = truncf(t3._average);
	_dataBase->AddInfo(t3);

	SortingForDatabase(E_Sort::SORT_LOW);

}

std::wstring GradeSystem::CreateDataLine(const Info<sData>* iData)
{
	wstring temp;
	temp = to_wstring(iData->_data._index);
	temp.append(L",");
	temp.append(iData->_data._name);
	temp.append(L",");
	temp.append(to_wstring(iData->_data._grade));
	temp.append(L",");
	temp.append(to_wstring(iData->_data._kor));
	temp.append(L",");
	temp.append(to_wstring(iData->_data._eng));
	temp.append(L",");
	temp.append(to_wstring(iData->_data._math));
	temp.append(L",");
	temp.append(to_wstring(iData->_data._total));
	temp.append(L",");
	temp.append(to_wstring(iData->_data._average));
	temp.append(L"\n");

	return temp;
}

void GradeSystem::StateInit()
{
	SystemState* mainState = new MainState();
	_stateList->push_back(mainState);
	SystemState* viewState = new ViewState();
	_stateList->push_back(viewState);
	SystemState* searchState = new SearchState();
	_stateList->push_back(searchState);
	SystemState* addState = new AddState();
	_stateList->push_back(addState);
	SystemState* delState = new DelState();
	_stateList->push_back(delState);
	SystemState* loadState = new LoadState();
	_stateList->push_back(loadState);
	SystemState* saveState = new SaveState();
	_stateList->push_back(saveState);
	SystemState* exitState = new ExitState();
	_stateList->push_back(exitState);
}

GradeSystem::GradeSystem()
{
	Init();

	SaveFile("", Gsys::E_SaveMode::SAVE_PREV, Gsys::E_SaveType::SAVE_TXT);
}

GradeSystem::~GradeSystem()
{
	delete	_state;
	delete	_dataBase;
	delete	_stateList;
	delete	_inFile;
	delete	_outFile;
}

bool GradeSystem::Run()
{
	if (_state == nullptr)
		return false;

	if (_state->Run(this))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void GradeSystem::SetState(E_SysState sType)
{
	switch (sType)
	{
	case E_SysState::SYSTEM_MAIN:
	{
		_state = (*_stateList)[(static_cast<int>(E_SysState::SYSTEM_MAIN))];
		break;
	}
	case E_SysState::SYSTEM_VIEW:
	{
		_state = (*_stateList)[(static_cast<int>(E_SysState::SYSTEM_VIEW))];
		break;
	}
	case E_SysState::SYSTEM_FIND:
	{
		_state = (*_stateList)[(static_cast<int>(E_SysState::SYSTEM_FIND))];
		break;
	}
	case E_SysState::SYSTEM_ADD:
	{
		_state = (*_stateList)[(static_cast<int>(E_SysState::SYSTEM_ADD))];
		break;
	}
	case E_SysState::SYSTEM_DELETE:
	{
		_state = (*_stateList)[(static_cast<int>(E_SysState::SYSTEM_DELETE))];
		break;
	}
	case E_SysState::SYSTEM_LOAD:
	{
		_state = (*_stateList)[(static_cast<int>(E_SysState::SYSTEM_LOAD))];
		break;
	}
	case E_SysState::SYSTEM_SAVE:
	{
		_state = (*_stateList)[(static_cast<int>(E_SysState::SYSTEM_SAVE))];
		break;
	}
	case E_SysState::SYSTEM_EXIT:
	{
		_state = (*_stateList)[(static_cast<int>(E_SysState::SYSTEM_EXIT))];
		break;
	}
	default:
		break;
	}
}

void GradeSystem::InsertionSortingHigh(Info<sData>* head, Info<sData>* tail)
{
	Info<sData>* _target = head->_next->_next;
	Info<sData>* _compare = _target->_prev;
	sData		 _temp;

	for (; _target != tail; _target = _target->_next)
	{
		_temp = _target->_data;
		for (_compare = _target->_prev; _compare != head; _compare = _compare->_prev)
		{
			if (_compare->_data._total > _temp._total)
			{
				_compare->_next->_data = _compare->_data;
			}
			else
				break;
		}
		_compare->_next->_data = _temp;
	}
}

void GradeSystem::InsertionSortingLow(Info<sData>* head, Info<sData>* tail)
{
	Info<sData>* _target = head->_next->_next;
	Info<sData>* _compare = _target->_prev;
	sData		 _temp;

	for (; _target != tail; _target = _target->_next)
	{
		_temp = _target->_data;
		for (_compare = _target->_prev; _compare != head; _compare = _compare->_prev)
		{
			if (_compare->_data._total < _temp._total)
			{
				_compare->_next->_data = _compare->_data;
			}
			else
				break;
		}
		_compare->_next->_data = _temp;
	}
}

void GradeSystem::SortingForDatabase(E_Sort type)
{
	switch (type)
	{
	case Gsys::E_Sort::SORT_HIGH:
	{
		_sortFun = &GradeSystem::InsertionSortingHigh;
		_dataBase->Sorting(_sortFun, this);
		break;
	}
	case Gsys::E_Sort::SORT_LOW:
	{
		_sortFun = &GradeSystem::InsertionSortingLow;
		_dataBase->Sorting(_sortFun, this);
		break;
	}
	default:
		break;
	}
}

bool GradeSystem::SaveFile(const char* fName, E_SaveMode sMode, E_SaveType sType)
{
	switch (sMode)
	{
	case E_SaveMode::SAVE_PREV:
	{
		if (sType == E_SaveType::SAVE_BIN)
		{
			string path = MYLOCALPATH_SAVE;
			path.append("save_prev.bin");

			_outFile->open(path, ios::binary);

			for (int i = 0; i < _dataBase->size(); i++)
			{
				Info<sData>* _tdata = _dataBase->SearchInfoForIndex(i);
				wstring  _tLine = CreateDataLine(_tdata);
				_outFile->write(_tLine.c_str(), _tLine.size());
			}

			_outFile->close();

			cout << endl;
			cout << "경로 : " << path << " <저장 완료>" << endl;
			return true;
		}
		else
		{
			string _path = MYLOCALPATH_SAVE;
			_path.append("save_prev.txt");

			_outFile->open(_path, ios_base::out);

			for (int i = 0; i < _dataBase->size(); i++)
			{
				Info<sData>* _tdata = _dataBase->SearchInfoForIndex(i);
				wstring  _tLine = CreateDataLine(_tdata);
				_outFile->write(_tLine.c_str(), _tLine.size());
			}

			_outFile->close();

			cout << endl;
			cout << "경로 : " <<  _path << " <저장 완료>" << endl;
			return true;
		}
		break;
	}
	case E_SaveMode::SAVE_NEW:
	{
		if (fName == nullptr)
			return false;

		if (sType == E_SaveType::SAVE_BIN)
		{
			string path = MYLOCALPATH_SAVE;
			path.append(fName);
			path.append(".bin");

			_outFile->open(path, ios::binary);

			for (int i = 0; i < _dataBase->size(); i++)
			{
				Info<sData>* _tdata = _dataBase->SearchInfoForIndex(i);
				wstring	_tLine = CreateDataLine(_tdata);
				_outFile->write(_tLine.c_str(), _tLine.size());
			}

			_outFile->close();

			cout << endl;
			cout << "경로 : " << path << " <저장 완료>" << endl;
			return true;
		}
		else
		{
			string path = MYLOCALPATH_SAVE;
			path.append(fName);
			path.append(".txt");

			_outFile->open(path);

			for (int i = 0; i < _dataBase->size(); i++)
			{
				Info<sData>* _tdata = _dataBase->SearchInfoForIndex(i);
				wstring  _tLine = CreateDataLine(_tdata);
				_outFile->write(_tLine.c_str(), _tLine.size());
			}

			_outFile->close();

			cout << endl;
			cout << "경로 : " << path << " <저장 완료>" << endl;
			return true;
		}
		break;
	}
	}

	return false;
}

bool GradeSystem::LoadFile(const char* fName, E_LoadMode lMode, E_LoadType lType)
{

	return false;
}

