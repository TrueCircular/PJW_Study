#include "GradeSystem.h"
#include "../systemState/SystemState.h"
//#include "../gradeList/GradeList.h"

void GradeSystem::Init()
{
	std::locale::global(std::locale("Korean"));
	//state
	_state = nullptr;
	_stateList = new StateList();
	StateInit();
	SetState(E_SysState::SYSTEM_MAIN);
	//data
	_dataBase = new GradeList<sData, GradeSystem>();
	_inFile = new wifstream();
	_outFile = new wofstream();
	//file
	LoadFile();
	SortingForDatabase();
}

wstring GradeSystem::CreateDataLine(const Info<sData>* iData)
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
	}
}

void GradeSystem::InsertionSortingHigh(Info<sData>* head, Info<sData>* tail, E_SortingType sType)
{
	Info<sData>* _target = head->_next->_next;
	Info<sData>* _compare = _target->_prev;
	sData		 _temp;

	for (; _target != tail; _target = _target->_next)
	{
		_temp = _target->_data;
		for (_compare = _target->_prev; _compare != head; _compare = _compare->_prev)
		{
			if (sType == E_SortingType::SORTING_NUMBER)
			{
				if (_compare->_data._index > _temp._index)
				{
					_compare->_next->_data = _compare->_data;
				}
				else
					break;
			}
			else if (sType == E_SortingType::SORTING_GRADE)
			{
				if (_compare->_data._grade > _temp._grade)
				{
					_compare->_next->_data = _compare->_data;
				}
				else
					break;
			}
			else if (sType == E_SortingType::SORINTG_KOR)
			{
				if (_compare->_data._kor > _temp._kor)
				{
					_compare->_next->_data = _compare->_data;
				}
				else
					break;
			}
			else if (sType == E_SortingType::SORTING_ENG)
			{
				if (_compare->_data._eng > _temp._eng)
				{
					_compare->_next->_data = _compare->_data;
				}
				else
					break;
			}
			else if (sType == E_SortingType::SORTING_MATH)
			{
				if (_compare->_data._math > _temp._math)
				{
					_compare->_next->_data = _compare->_data;
				}
				else
					break;
			}
			else if (sType == E_SortingType::SORTING_TOTAL)
			{
				if (_compare->_data._total > _temp._total)
				{
					_compare->_next->_data = _compare->_data;
				}
				else
					break;
			}
			else if (sType == E_SortingType::SORTING_AVERAGE)
			{
				if (_compare->_data._average > _temp._average)
				{
					_compare->_next->_data = _compare->_data;
				}
				else
					break;
			}		
		}
		_compare->_next->_data = _temp;
	}
}

void GradeSystem::InsertionSortingLow(Info<sData>* head, Info<sData>* tail, E_SortingType sType)
{
	Info<sData>* _target = head->_next->_next;
	Info<sData>* _compare = _target->_prev;
	sData		 _temp;

	for (; _target != tail; _target = _target->_next)
	{
		_temp = _target->_data;
		for (_compare = _target->_prev; _compare != head; _compare = _compare->_prev)
		{
			if (sType == E_SortingType::SORTING_NUMBER)
			{
				if (_compare->_data._index < _temp._index)
				{
					_compare->_next->_data = _compare->_data;
				}
				else
					break;
			}
			else if (sType == E_SortingType::SORTING_GRADE)
			{
				if (_compare->_data._grade < _temp._grade)
				{
					_compare->_next->_data = _compare->_data;
				}
				else
					break;
			}
			else if (sType == E_SortingType::SORINTG_KOR)
			{
				if (_compare->_data._kor < _temp._kor)
				{
					_compare->_next->_data = _compare->_data;
				}
				else
					break;
			}
			else if (sType == E_SortingType::SORTING_ENG)
			{
				if (_compare->_data._eng < _temp._eng)
				{
					_compare->_next->_data = _compare->_data;
				}
				else
					break;
			}
			else if (sType == E_SortingType::SORTING_MATH)
			{
				if (_compare->_data._math < _temp._math)
				{
					_compare->_next->_data = _compare->_data;
				}
				else
					break;
			}
			else if (sType == E_SortingType::SORTING_TOTAL)
			{
				if (_compare->_data._total < _temp._total)
				{
					_compare->_next->_data = _compare->_data;
				}
				else
					break;
			}
			else if (sType == E_SortingType::SORTING_AVERAGE)
			{
				if (_compare->_data._average < _temp._average)
				{
					_compare->_next->_data = _compare->_data;
				}
				else
					break;
			}
		}
		_compare->_next->_data = _temp;
	}
}

sData GradeSystem::CreateLoadData(DynamicArray<std::wstring>* list)
{
	sData tData;

	tData._index = std::stoi((*list)[0]);
	tData._name = (*list)[1];
	tData._grade = stoi((*list)[2]);
	tData._kor = stoi((*list)[3]);
	tData._eng = stoi((*list)[4]);
	tData._math = stoi((*list)[5]);
	tData._total = stoi((*list)[6]);
	tData._average = stof((*list)[7]);

	return tData;
}

bool GradeSystem::LoadData(const std::string& path)
{
	//파일 오픈 예외처리
	_inFile->open(path);
	if (!_inFile->good())
	{
		std::cerr << "파일을 열 수 없습니다. PATH :" << path << endl;
		return false;
	}
	if (_dataBase->size() > 0)
		_dataBase->AllDelete();
	//버퍼
	wstring wTemp;
	DynamicArray<wstring> wList;
	//개행 읽기
	while (std::getline(*_inFile, wTemp))
	{
		wList.push_back(wTemp);
	}
	//split 버퍼
	wstringstream* wStream = new wstringstream();
	DynamicArray<wstring>* parts = new DynamicArray<wstring>();
	//database에 저장
	for (int i = 0; i < wList.size(); i++)
	{
		wstring in = wList[i].substr(), temp;
		wStream->str(in);
		sData tData;
		while (std::getline(*wStream, temp, L','))
		{
			parts->push_back(temp);
		}
		tData = CreateLoadData(parts);
		_dataBase->AddInfo(tData);

		parts->clear();
		wStream->clear();
	}
	//complete call
	cout << "경로 :" << path << " <불러오기 완료>" << endl;
	//파일 닫기
	_inFile->close();

	delete parts;
	delete wStream;

	return true;
}

bool GradeSystem::SaveData(const std::string& path, E_SaveType sType)
{
	if (sType == E_SaveType::SAVE_BIN)
	{
		_outFile->open(path, ios::binary);
		if (!_outFile->good())
		{
			std::cerr << "파일을 저장 할 수 없습니다. PATH :" << path << endl;
			return false;
		}
	}
	else if (sType == E_SaveType::SAVE_TXT)
	{
		_outFile->open(path);
		if (!_outFile->good())
		{
			std::cerr << "파일을 저장 할 수 없습니다. PATH :" << path << endl;
			return false;
		}
	}
	if (_dataBase->size() <= 0)
	{
		std::cerr << "파일을 저장 할 수 없습니다. PATH :" << path << endl;
		return false;
	}

	for (int i = 0; i < _dataBase->size(); i++)
	{
		Info<sData>* _tdata = _dataBase->SearchInfoForIndex(i);
		wstring  _tLine = CreateDataLine(_tdata);
		_outFile->write(_tLine.c_str(), _tLine.size());
	}

	_outFile->close();

	cout << "경로 : " << path << " <저장 완료>" << endl;
	cout << "=================================================================" << endl;

	return true;
}

void GradeSystem::SortingForDatabase(E_Sort type, E_SortingType sType)
{
	switch (type)
	{
	case Gsys::E_Sort::SORT_HIGH:
	{
		_sortFun = &GradeSystem::InsertionSortingHigh;
		_dataBase->Sorting(_sortFun, this, sType);
		break;
	}
	case Gsys::E_Sort::SORT_LOW:
	{
		_sortFun = &GradeSystem::InsertionSortingLow;
		_dataBase->Sorting(_sortFun, this, sType);
		break;
	}
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
			//경로 설정
			string path = MYLOCALPATH_SAVE;
			path.append("save_prev.bin");
			std::filesystem::path _path(path);
			_path = std::filesystem::absolute(_path);
			//파일 저장
			return SaveData(_path.string(), sType);
		}
		else
		{
			//경로 설정
			string path = MYLOCALPATH_SAVE;
			path.append("save_prev.txt");
			std::filesystem::path _path(path);
			_path = std::filesystem::absolute(_path);
			//파일 저장
			return SaveData(_path.string(), sType);
		}
		break;
	}
	case E_SaveMode::SAVE_NEW:
	{
		if (fName == nullptr)
			return false;

		if (sType == E_SaveType::SAVE_BIN)
		{
			//경로 설정
			string path = MYLOCALPATH_SAVE;
			path.append(fName);
			path.append(".bin");
			std::filesystem::path _path(path);
			_path = std::filesystem::absolute(_path);
			//파일 저장
			return SaveData(_path.string(), sType);
		}
		else
		{
			//경로 설정
			string path = MYLOCALPATH_SAVE;
			path.append(fName);
			path.append(".txt");
			std::filesystem::path _path(path);
			_path = std::filesystem::absolute(_path);
			//파일 저장
			return SaveData(_path.string(), sType);
		}
		break;
	}
	}

	return false;
}

bool GradeSystem::LoadFile(const char* fName, E_LoadMode lMode, E_LoadType lType)
{
	switch (lMode)
	{
	case Gsys::E_LoadMode::LOAD_PREV:
	{
		switch (lType)
		{
		case Gsys::E_LoadType::LOAD_TXT:
		{
			//경로 설정
			string path = MYLOCALPATH_SAVE;
			path.append("save_prev.txt");
			std::filesystem::path _path(path);
			_path = std::filesystem::absolute(_path);
			//파일 로드
			return LoadData(_path.string());	
		}
		case Gsys::E_LoadType::LOAD_BIN:
		{
			//경로 설정
			string path = MYLOCALPATH_SAVE;
			path.append("save_prev.bin");
			std::filesystem::path _path(path);
			_path = std::filesystem::absolute(_path);
			//파일 로드
			return LoadData(_path.string());
		}
		}
		break;
	}
	case Gsys::E_LoadMode::LOAD_NEW:
	{
		switch (lType)
		{
		case Gsys::E_LoadType::LOAD_TXT:
		{
			//경로 설정
			string path = MYLOCALPATH_SAVE;
			path.append(fName);
			path.append(".txt");
			std::filesystem::path _path(path);
			_path = std::filesystem::absolute(_path);
			//파일 로드
			return LoadData(_path.string());
		}
		case Gsys::E_LoadType::LOAD_BIN:
		{
			//경로 설정
			string path = MYLOCALPATH_SAVE;
			path.append(fName);
			path.append(".bin");
			std::filesystem::path _path(path);
			_path = std::filesystem::absolute(_path);
			//파일 로드
			return LoadData(_path.string());
		}
		}
		break;
	}
	}

	return false;
}

