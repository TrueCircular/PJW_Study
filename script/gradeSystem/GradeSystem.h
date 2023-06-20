#pragma once
#include <fstream>
#include "../gradeList/GradeList.h"
#include <string>
#include <sstream>
#include <locale>
#include <conio.h>
#include <io.h>

#define MYLOCALPATH_SAVE (const char*)"../../data/Gsys_Save/"
#define MYLOCALPATH_LOAD (const char*)"../../data/Gsys_Load/"
#define MAX_SAVE_FILE 50

namespace Gsys
{
#pragma region E_State
	enum class E_SysState
	{
		SYSTEM_MAIN,
		SYSTEM_VIEW,
		SYSTEM_FIND,
		SYSTEM_ADD,
		SYSTEM_DELETE,
		SYSTEM_LOAD,
		SYSTEM_SAVE,
		SYSTEM_EXIT,
		NONE = 99
	};
#pragma endregion

#pragma region E_SaveMode
	enum class E_SaveMode
	{
		SAVE_PREV,
		SAVE_NEW
	};
	enum class E_SaveType
	{
		SAVE_TXT,
		SAVE_BIN
	};
#pragma endregion

#pragma region E_LoadMode
	enum class E_LoadMode
	{
		LOAD_PREV,
		LOAD_NEW
	};
	enum class E_LoadType
	{
		LOAD_TXT,
		LOAD_BIN
	};

#pragma endregion

#pragma region DataType
	struct sData
	{
		int				_index;
		std::wstring	_name;
		int				_grade;
		int				_kor;
		int				_eng;
		int				_math;
		int				_total;
		float			_average;

		sData() : _index(0), _name(L""), _grade(0),
				_kor(0), _eng(0), _math(0), _total(0), _average(0.f) {}
	};
#pragma endregion
}

#pragma region F_declaration
class SystemState;
class ViewState;
class AddState;
class DelState;
class SearchState;
class LoadState;
class SaveState;
class ExitState;
class MainState;
#pragma endregion

using namespace Gsys;

#pragma region DynamicArray

template<class T>
class DynamicArray
{
private:
	T*	_array;
	int _used;
	int _size;
public:
	DynamicArray() : _size(1), _used(0)
	{
		_array = new T[_size];
	}
	~DynamicArray() { delete[] _array; }

	void push_back(const T& data);
	void pop_back();
	void clear();
	int size() { return _size; }

	T& operator[](int index) { return this->_array[index]; }
};
#pragma endregion

#pragma region GradeSystem
class GradeSystem
{
private:
	typedef DynamicArray<SystemState**> StateAddress;
	typedef DynamicArray<SystemState*>	StateList;

	SystemState*		_state;
	GradeList<sData>*	_dataBase;
	StateList*			_stateList;
	std::wifstream*		_iFile;
	std::wofstream*		_oFile;
private:
	std::wstring CreateDataLine(const Info<sData>* iData);
	void StateInit();
public:
	GradeSystem();
	~GradeSystem();

	//state run
	bool Run();
	//state get,set
	SystemState* GetState() const { return _state; }
	void SetState(E_SysState sType);
	//datalist get
	GradeList<sData>* GetDataBase() const { return _dataBase; }
	//file, data
	bool	SaveFile(const char* fName = nullptr, E_SaveMode sMode = E_SaveMode::SAVE_PREV, E_SaveType sType = E_SaveType::SAVE_BIN);
	bool	LoadFile(const char* fName = nullptr, E_LoadMode lMode = E_LoadMode::LOAD_PREV, E_LoadType lType = E_LoadType::LOAD_BIN);
	sData	OutData(Info<sData>* data);
	void	PrintForAllSaveList();
};
#pragma endregion

#pragma region D_ArrayFun
template<class T>
inline void DynamicArray<T>::push_back(const T& data)
{
	if (_size > _used)
	{
		_array[_used] = data;
		_used++;
		return;
	}

	T* temp = new T[_size];

	for (int i = 0; i < _used; i++)
	{
		temp[i] = _array[i];
	}

	delete[] _array;

	_size *= 2;
	_array = new T[_size];

	for (int i = 0; i < _used; i++)
	{
		_array[i] = temp[i];
	}

	_array[_used] = data;
	_used++;

	delete[] temp;
}

template<class T>
inline void DynamicArray<T>::pop_back()
{
	if (_used == 0) return;

	_used--;

	T* temp = new T[_used];

	for (int i = 0; i < _used; i++)
	{
		temp[i] = _array[i];
	}

	delete[] _array;

	_array = new T[_size];

	for (int i = 0; i < _used; i++)
	{
		_array[i] = temp[i];
	}

	delete[] temp;
}
template<class T>
inline void DynamicArray<T>::clear()
{
	_used = 0;
	_size = 1;

	T* temp = new T[_used];

	delete[] _array;

	_array = temp;
}
#pragma endregion
