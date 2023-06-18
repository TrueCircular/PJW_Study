#pragma once
#include "../gradeList/GradeList.h"

namespace Gsys
{
#pragma region E_State
	enum class E_SysState
	{
		SYSTEM_MAIN,
		SYSTEM_VIEW,
		SYSTEM_ADD,
		SYSTEM_DELETE,
		SYSTEM_LOAD,
		SYSTEM_SAVE,
		SYSTEM_EXIT,
		NONE = 99
	};
#pragma endregion

#pragma region DataType
	struct sData
	{
		int		_index;
		char* _name;
		int		_grade;
		int		_kor;
		int		_eng;
		int		_math;
		int		_total;
		float	_average;

		sData() : _index(0), _name(nullptr), _grade(0),
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
	void pop_back(const T& data);
	int size() { return _size; }

	T& operator[](int index) { return this->_array[index]; }
};
#pragma endregion

#pragma region GradeSystem
class GradeSystem
{
private:
	typedef DynamicArray<SystemState**> StateAddress;

	SystemState*		_state;
	GradeList<sData>*	_dataBase;
	StateAddress*		_addRess;
	FILE*				_file;
public:
	GradeSystem();
	~GradeSystem();

	//state run
	bool Run();
	//state get,set
	SystemState* GetState() const { return _state; }
	void SetState(SystemState* state) { _state = state; }
	//datalist get
	GradeList<sData>* GetDataBase() const { return _dataBase; }
	//state address get
	StateAddress* GetAddressList() const { return _addRess; }
	//file, data
	FILE*	GetFile() const { return _file; }
	bool	SaveFile();
	bool	LoadFile();
	sData	OutData(Info<sData>* data);
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
inline void DynamicArray<T>::pop_back(const T& data)
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
#pragma endregion
