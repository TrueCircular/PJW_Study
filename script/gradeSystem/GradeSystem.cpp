#include "GradeSystem.h"
#include "../systemState/SystemState.h"


GradeSystem::GradeSystem()
{
	_state = new MainState();
	_dataBase = new GradeList<sData>();
	_addRess = new StateAddress();
	_file = new FILE();

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

bool GradeSystem::SaveFile()
{
	return false;
}

bool GradeSystem::LoadFile()
{
	return false;
}

sData GradeSystem::OutData(Info<sData>* data)
{
	sData dTemp = data->_data;

	return dTemp;
}
