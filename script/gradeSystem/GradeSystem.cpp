#include "GradeSystem.h"
#include "../systemState/SystemState.h"


std::wstring GradeSystem::CreateDataLine(const Info<sData>* iData)
{
	wstring temp = to_wstring(iData->_data._index);
	temp += L",";
	temp += (iData->_data._name);
	temp += L",";
	temp += to_wstring(iData->_data._grade);
	temp += L",";
	temp += to_wstring(iData->_data._kor);
	temp += L",";
	temp += to_wstring(iData->_data._eng);
	temp += L",";
	temp += to_wstring(iData->_data._math);
	temp += L",";
	temp += to_wstring(iData->_data._total);
	temp += L",";
	temp += to_wstring(iData->_data._average);
	temp += L"\n";

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
	std::locale::global(std::locale("Korean"));
	_stateList = new StateList();

	StateInit();
	SetState(E_SysState::SYSTEM_MAIN);

	_dataBase = new GradeList<sData>();
	_iFile = new std::wifstream();
	_oFile = new std::wofstream();

}

GradeSystem::~GradeSystem()
{
	delete	_state;
	delete	_dataBase;
	delete	_stateList;
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
		_state = _stateList->operator[](static_cast<int>(E_SysState::SYSTEM_MAIN));
		break;
	}
	case E_SysState::SYSTEM_VIEW:
	{
		_state = _stateList->operator[](static_cast<int>(E_SysState::SYSTEM_VIEW));
		break;
	}
	case E_SysState::SYSTEM_FIND:
	{
		_state = _stateList->operator[](static_cast<int>(E_SysState::SYSTEM_FIND));
		break;
	}
	case E_SysState::SYSTEM_ADD:
	{
		_state = _stateList->operator[](static_cast<int>(E_SysState::SYSTEM_ADD));
		break;
	}
	case E_SysState::SYSTEM_DELETE:
	{
		_state = _stateList->operator[](static_cast<int>(E_SysState::SYSTEM_DELETE));
		break;
	}
	case E_SysState::SYSTEM_LOAD:
	{
		_state = _stateList->operator[](static_cast<int>(E_SysState::SYSTEM_LOAD));
		break;
	}
	case E_SysState::SYSTEM_SAVE:
	{
		_state = _stateList->operator[](static_cast<int>(E_SysState::SYSTEM_SAVE));
		break;
	}
	case E_SysState::SYSTEM_EXIT:
	{
		_state = _stateList->operator[](static_cast<int>(E_SysState::SYSTEM_EXIT));
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

			_oFile->open(path, ios::binary);

			for (int i = 0; i < _dataBase->size(); i++)
			{
				Info<sData>* _tdata = _dataBase->SearchInfoForIndex(i);
				wstring  _tLine = CreateDataLine(_tdata);
				_oFile->write(_tLine.c_str(), _tLine.size());
			}

			_oFile->close();
			return true;
		}
		else
		{
			string path = MYLOCALPATH_SAVE;
			path.append("save_prev.txt");
			
			_oFile->open(path);

			for (int i = 0; i < _dataBase->size(); i++)
			{
				Info<sData>* _tdata = _dataBase->SearchInfoForIndex(i);
				wstring  _tLine = CreateDataLine(_tdata);
				_oFile->write(_tLine.c_str(), _tLine.size());
			}

			_oFile->close();
			return true;
		}
		break;
	}
	case E_SaveMode::SAVE_NEW:
	{
		if (sType == E_SaveType::SAVE_BIN)
		{
			string path = MYLOCALPATH_SAVE;
			path.append(fName);
			path.append(".bin");

			_oFile->open(path, ios::binary);

			for (int i = 0; i < _dataBase->size(); i++)
			{
				Info<sData>* _tdata = _dataBase->SearchInfoForIndex(i);
				wstring  _tLine = CreateDataLine(_tdata);
				_oFile->write(_tLine.c_str(), _tLine.size());
			}

			_oFile->close();
			return true;
		}
		else
		{
			string path = MYLOCALPATH_SAVE;
			path.append(fName);
			path.append(".txt");

			_oFile->open(path);

			for (int i = 0; i < _dataBase->size(); i++)
			{
				Info<sData>* _tdata = _dataBase->SearchInfoForIndex(i);
				wstring  _tLine = CreateDataLine(_tdata);
				_oFile->write(_tLine.c_str(), _tLine.size());
			}

			_oFile->close();
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

sData GradeSystem::OutData(Info<sData>* data)
{
	sData dTemp = data->_data;

	return dTemp;
}
