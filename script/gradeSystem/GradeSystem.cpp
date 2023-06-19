#include "GradeSystem.h"
#include "../systemState/SystemState.h"

std::wstring GradeSystem::CreateInfoWString(Info<sData> data)
{
	std::wstring fBuffer = L"";

	fBuffer = L"번호 : ";
	fBuffer += data._data._index;
	fBuffer += L" 이름 : ";
	fBuffer += data._data._name;
	fBuffer += L" 학년 : ";
	fBuffer += data._data._grade;
	fBuffer += L" 국어 : ";
	fBuffer += data._data._kor;
	fBuffer += L" 수학 : ";
	fBuffer += data._data._math;
	fBuffer += L" 영어 : ";
	fBuffer += data._data._eng;
	fBuffer += L" 총점 : ";
	fBuffer += data._data._total;
	fBuffer += L" 평균 : ";
	fBuffer += data._data._average;
	fBuffer += L"\n";

	return fBuffer;
}

GradeSystem::GradeSystem()
{
	std::locale::global(std::locale("Korean"));

	_state = new MainState();
	_dataBase = new GradeList<sData>();
	_addRess = new StateAddress();
	_iFile = new std::wifstream();
	_oFile = new std::wofstream();

	_addRess->push_back(&_state);
}

GradeSystem::~GradeSystem()
{
	delete	_state;
	delete	_dataBase;

	for (int i = 0; i < _addRess->size(); i++)
	{
		delete& _addRess[i];
	}
	delete _addRess;
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

bool GradeSystem::SaveFile(const char* path, const char* fName)
{
	//로드된 데이터가 없으면 retrun
	if (_dataBase->size() == 0)
		return false;
	//경로 생성
	const char* myPath = "../../data/Gsys_Save" + *path;
	//버퍼
	std::wstring fBuffer = L"";
	//새로운 세이브 파일 생성
	if (fName != NULL)
	{
		//출력 파일 열기
		_oFile->open(fName);
		//데이터 파싱
		for (int i = 0; i < _dataBase->size(); i++)
		{
			Info<sData>* temp = _dataBase->SearchInfoForIndex(i);
			fBuffer = CreateInfoWString(*temp);
			*_oFile << fBuffer;
		}
		//출력 파일 닫기
		_oFile->close();
		
		return true;
	}
	//기존 세이브 파일 덮어쓰기
	else
	{
		//출력 파일 열기
		_oFile->open(path);
		//데이터 파싱
		for (int i = 0; i < _dataBase->size(); i++)
		{
			Info<sData>* temp = _dataBase->SearchInfoForIndex(i);
			fBuffer = CreateInfoWString(*temp);
			*_oFile << fBuffer;
		}
		//출력 파일 닫기
		_oFile->close();

		return true;
	}

	return false;
}

bool GradeSystem::LoadFile(const char* path)
{
	return false;
}

sData GradeSystem::OutData(Info<sData>* data)
{
	sData dTemp = data->_data;

	return dTemp;
}
