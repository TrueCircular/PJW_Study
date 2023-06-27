#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <locale>
#include <cmath>
#include "../gradeList/GradeList.h"

#define MYLOCALPATH_SAVE (const char*)"data/Gsys_Save/"
#define MAX_SAVE_FILE 50

namespace Gsys
{
	enum class E_Sort
	{
		SORT_HIGH,
		SORT_LOW
	};
	enum class E_SortingType
	{
		SORTING_NUMBER,
		SORTING_GRADE,
		SORINTG_KOR,
		SORTING_ENG,
		SORTING_MATH,
		SORTING_TOTAL,
		SORTING_AVERAGE
	};

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

		bool operator==(const sData& input)
		{
			return  (_index == input._index) &&
					(_name == input._name) &&
					(_grade == input._grade) &&
					(_kor == input._kor) &&
					(_eng == input._eng) &&
					(_math == input._math) &&
					(_total == input._total) &&
					(_average == input._average);
		}
		sData& operator=(const sData& input)
		{
			_index = input._index;
			_name = input._name;
			_grade = input._grade;
			_kor = input._kor;
			_eng = input._eng;
			_math = input._math;
			_total = input._total;
			_average = input._average;

			return *this;
		}
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
//template<typename T> class Info;
//template<typename T, typename N> class GradeList;
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

	T& operator[](int index)
	{
		if (index < 0 || index >= _size)
			std::exit(1);
		else
			return this->_array[index];
	}
};
#pragma endregion

#pragma region GradeSystem
class GradeSystem
{
private:
	typedef DynamicArray<SystemState*>	StateList;
	typedef void (GradeSystem:: * Sorting_Fun)(Info<sData>*, Info<sData>*, E_SortingType);

	SystemState*					_state;
	GradeList<sData, GradeSystem>*	_dataBase;
	StateList*						_stateList;
	std::wifstream*					_inFile;
	std::wofstream*					_outFile;
	Sorting_Fun						_sortFun;
private:
	void Init();
	std::wstring CreateDataLine(const Info<sData>* iData);
	void StateInit();
	void InsertionSortingHigh(Info<sData>* head, Info<sData>* tail, E_SortingType sType);
	void InsertionSortingLow(Info<sData>* head, Info<sData>* tail, E_SortingType sType);
	sData CreateLoadData(DynamicArray<std::wstring>* list);
public:
	GradeSystem();
	~GradeSystem();

	//state run
	bool Run();
	//state get,set
	SystemState* GetState() const { return _state; }
	void SetState(E_SysState sType);
	//datalist get, fun
	GradeList<sData, GradeSystem>* GetDataBase() const { return _dataBase; }
	void SortingForDatabase(E_Sort type = E_Sort::SORT_HIGH, E_SortingType sType = E_SortingType::SORTING_NUMBER);
	//file, data
	bool SaveFile(const char* fName = nullptr, E_SaveMode sMode = E_SaveMode::SAVE_PREV, E_SaveType sType = E_SaveType::SAVE_BIN);
	bool LoadFile(const char* fName = nullptr, E_LoadMode lMode = E_LoadMode::LOAD_PREV, E_LoadType lType = E_LoadType::LOAD_BIN);
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

	delete[] _array;

	_array = new T[_size];
}
#pragma endregion
