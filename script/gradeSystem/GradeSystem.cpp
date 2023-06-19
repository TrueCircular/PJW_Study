#include "GradeSystem.h"
#include "../systemState/SystemState.h"

std::wstring GradeSystem::CreateInfoWString(Info<sData> data)
{
	std::wstring fBuffer = L"";

	fBuffer = L"��ȣ : ";
	fBuffer += data._data._index;
	fBuffer += L" �̸� : ";
	fBuffer += data._data._name;
	fBuffer += L" �г� : ";
	fBuffer += data._data._grade;
	fBuffer += L" ���� : ";
	fBuffer += data._data._kor;
	fBuffer += L" ���� : ";
	fBuffer += data._data._math;
	fBuffer += L" ���� : ";
	fBuffer += data._data._eng;
	fBuffer += L" ���� : ";
	fBuffer += data._data._total;
	fBuffer += L" ��� : ";
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
	//�ε�� �����Ͱ� ������ retrun
	if (_dataBase->size() == 0)
		return false;
	//��� ����
	const char* myPath = "../../data/Gsys_Save" + *path;
	//����
	std::wstring fBuffer = L"";
	//���ο� ���̺� ���� ����
	if (fName != NULL)
	{
		//��� ���� ����
		_oFile->open(fName);
		//������ �Ľ�
		for (int i = 0; i < _dataBase->size(); i++)
		{
			Info<sData>* temp = _dataBase->SearchInfoForIndex(i);
			fBuffer = CreateInfoWString(*temp);
			*_oFile << fBuffer;
		}
		//��� ���� �ݱ�
		_oFile->close();
		
		return true;
	}
	//���� ���̺� ���� �����
	else
	{
		//��� ���� ����
		_oFile->open(path);
		//������ �Ľ�
		for (int i = 0; i < _dataBase->size(); i++)
		{
			Info<sData>* temp = _dataBase->SearchInfoForIndex(i);
			fBuffer = CreateInfoWString(*temp);
			*_oFile << fBuffer;
		}
		//��� ���� �ݱ�
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
