#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <locale>


#define MYLOCALPATH_SAVE (const char*)"../../data/Gsys_Save/"
#define MAX_SAVE_FILE 50

using namespace std;



namespace Gsys
{
	enum class E_Sort
	{
		SORT_HIGH,
		SORT_LOW
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
using namespace Gsys;



#pragma region GradeList
template<typename T>
class Info
{
public:
	Info() : _prev(nullptr), _next(nullptr), _data(T()), _id(0) {}
	Info(const T& value) : _prev(nullptr), _next(nullptr), _data(value), _id(0) {}
public:
	Info* _prev;
	Info* _next;
	T		_data;
	int		_id;
};

template<typename T, typename N>
class GradeList
{
private:
	typedef void(N::* Sorting_Fun)(Info<T>*, Info<T>*);

	Info<T>* _head;
	Info<T>* _tail;
	int		 _size;
private:
	Info<T>* AddNode(Info<T>* node, const T& data);
	Info<T>* DelNode(Info<T>* node);
	Info<T>* FindNode(Info<T>* node, const T& value);
	Info<T>* FindeNodeForIndex(int idex);
	Info<T>* InsertNode(Info<T>* node, const T& data);
	void DelBack();
public:
	GradeList();
	~GradeList();

	void AddInfo(const T& value);
	void DeleteInfo(const T& value);
	void InsertInfo(const T& value1, const T& value2);
	Info<T>* SearchInfo(const T& value);
	Info<T>* SearchInfoForIndex(int idex);
	bool Sorting(Sorting_Fun fun, N* ptr);
	void AllDelete();
	int size() { return _size; }
};
#pragma endregion

#pragma region G_Fun
template<typename T, typename N>
inline GradeList<T, N>::~GradeList()
{
	AllDelete();
}

template<typename T, typename N>
inline Info<T>* GradeList<T, N>::AddNode(Info<T>* node, const T& data)
{
	if (node == nullptr)
		return nullptr;

	Info<T>* tNode = new Info<T>(data);
	Info<T>* pNode = node->_prev;

	pNode->_next = tNode;
	tNode->_prev = pNode;

	tNode->_next = node;
	node->_prev = tNode;

	tNode->_id = _size;
	_size++;

	return tNode;
	return nullptr;
}

template<typename T, typename N>
inline Info<T>* GradeList<T, N>::DelNode(Info<T>* node)
{
	if (node == nullptr)
		return nullptr;

	Info<T>* pNode = node->_prev;
	Info<T>* nNode = node->_next;

	pNode->_next = nNode;
	nNode->_prev = pNode;

	delete node;

	_size--;

	return nNode;
}

template<typename T, typename N>
inline Info<T>* GradeList<T, N>::FindNode(Info<T>* node, const T& value)
{
	//if (node == nullptr)
	//	return nullptr;

	Info<T>* nFind = node;

	while (nFind != _tail)
	{
		if (nFind->_data == value)
			return nFind;
		else
			nFind = nFind->_next;
	}

	return nullptr;
}

template<typename T, typename N>
inline Info<T>* GradeList<T, N>::FindeNodeForIndex(int idex)
{
	Info<T>* nFind = _head->_next;

	while (nFind != _tail)
	{
		if (nFind->_id == idex)
			return nFind;
		else
			nFind = nFind->_next;
	}

	return nullptr;
}

template<typename T, typename N>
inline Info<T>* GradeList<T, N>::InsertNode(Info<T>* node, const T& data)
{
	if (node == nullptr)
		return nullptr;

	Info<T>* nFind = node;
	Info<T>* nNext = nFind->_next;
	Info<T>* iNode = new Info<T>(data);

	nFind->_next = iNode;
	iNode->_prev = nFind;
	iNode->_next = nNext;
	nNext->_prev = iNode;

	_size++;

	return nNext;
}

template<typename T, typename N>
inline void GradeList<T, N>::DelBack()
{
	DelNode(_tail->_prev);
}

template<typename T, typename N>
inline GradeList<T, N>::GradeList()
{
	_head = new Info<T>();
	_tail = new Info<T>();
	_size = 0;

	_head->_prev = nullptr;
	_head->_next = _tail;
	_tail->_prev = _head;
	_tail->_next = nullptr;
}

template<typename T, typename N>
inline void GradeList<T, N>::AddInfo(const T& value) //data push back
{
	AddNode(_tail, value);
}

template<typename T, typename N>
inline void GradeList<T, N>::DeleteInfo(const T& value)
{
	DelNode(FindNode(_head, value));
}

template<typename T, typename N>
inline void GradeList<T, N>::InsertInfo(const T& value1, const T& value2) //value1 : in dest.. value2 : newData
{
	InsertNode(FindNode(_head, value1), value2);
}

template<typename T, typename N>
inline Info<T>* GradeList<T, N>::SearchInfo(const T& value) //if find value return node
{
	if (FindNode(_head, value) != nullptr)
	{
		Info<T>* temp = FindNode(_head, value);
		return temp;
	}

	return nullptr;
}

template<typename T, typename N>
inline Info<T>* GradeList<T, N>::SearchInfoForIndex(int idex)
{
	if (FindeNodeForIndex(idex) != nullptr)
	{
		Info<T>* temp = FindeNodeForIndex(idex);
		return temp;
	}

	return nullptr;
}

template<typename T, typename N>
inline bool GradeList<T, N>::Sorting(Sorting_Fun fun, N* ptr)
{
	(ptr->*fun)(_head, _tail);

	return true;
}

template<typename T, typename N>
inline void GradeList<T, N>::AllDelete()
{
	while (_size > 0)
	{
		DelBack();
	}
	delete _head;
	delete _tail;
}
#pragma endregion

#pragma region DynamicArray

template<class T>
class DynamicArray
{
private:
	T* _array;
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

	if (_array)
	{
		_used = 0;
		_size = 1;

		delete[] _array;

		_array = new T[_size];
	}

}
#pragma endregion


class sortclass
{
public:
	sortclass(){}
	~sortclass(){}

	void InsertionSortingHigh(Info<sData>* head, Info<sData>* tail)
	{
		Info<sData>* _target = head->_next->_next;
		Info<sData>* _compare = _target->_prev;
		sData	_temp;

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

};


typedef void(sortclass::*Sort_fun)(Info<Gsys::sData>*, Info<Gsys::sData>*);

std::wstring CreateDataLine(const Info<sData>* iData);
bool SaveFile(const char* fName = nullptr,	Gsys::E_SaveMode sMode = E_SaveMode::SAVE_PREV, Gsys::E_SaveType sType = E_SaveType::SAVE_BIN);
bool LoadFile(const char* fName = nullptr,	Gsys::E_LoadMode lMode = E_LoadMode::LOAD_PREV, Gsys::E_LoadType lType = E_LoadType::LOAD_BIN);
sData CreateLoadData(DynamicArray<wstring>* list);

std::wifstream* _iFile;
std::wofstream* _oFile;

GradeList<sData, sortclass>* _dataBase;




int main()
{
	Gsys::sData t1;
	t1._total = 100;
	wstring na1 = L"김일병";
	t1._name = na1;
	Gsys::sData t2;
	t2._total = 300;
	wstring na2 = L"김이병";
	t2._name = na2;
	Gsys::sData t3;
	t3._total = 200;
	wstring na3 = L"김삼병";
	t3._name = na3;

	sortclass* temp = new sortclass();
	Sort_fun fun = &sortclass::InsertionSortingHigh;



	_dataBase = new GradeList<sData, sortclass>();
	_dataBase->AddInfo(t1);
	_dataBase->AddInfo(t2);
	_dataBase->AddInfo(t3);

	//cout << tList->SearchInfo(t2)->_data._total << endl;

	_dataBase->Sorting(fun, temp);

	int tt = _dataBase->SearchInfoForIndex(2)->_data._total;

	cout << tt << endl;

	std::locale::global(std::locale("Korean"));

	_oFile = new wofstream();
	_iFile = new wifstream();

	//SaveFile("", Gsys::E_SaveMode::SAVE_PREV, Gsys::E_SaveType::SAVE_TXT);
	//SaveFile("test", Gsys::E_SaveMode::SAVE_NEW, Gsys::E_SaveType::SAVE_TXT);

	LoadFile("", E_LoadMode::LOAD_PREV, E_LoadType::LOAD_TXT);

	//cout << tList->size() << endl;

	delete _dataBase;
	delete temp;
	delete _oFile;

}

bool SaveFile(const char* fName, Gsys::E_SaveMode sMode, Gsys::E_SaveType sType)
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

			cout << endl;
			cout << path << " 세이브 완료" << endl;
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

			_oFile->open(path, ios::binary);

			for (int i = 0; i < _dataBase->size(); i++)
			{
				Info<sData>* _tdata = _dataBase->SearchInfoForIndex(i);
				wstring	_tLine = CreateDataLine(_tdata);
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

			cout << endl;
			cout << path << " 세이브 완료" << endl;

			return true;
		}
		break;
	}
	}

	return false;
}

bool LoadFile(const char* fName, Gsys::E_LoadMode lMode, Gsys::E_LoadType lType)
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
			//파일 오픈
			_iFile->open(path);
			//버퍼
			wstring wTemp;
			DynamicArray<wstring> wList;
			//개행 읽기
			while (std::getline(*_iFile, wTemp))
			{
				wList.push_back(wTemp);
			}
			//split 버퍼
			wstringstream* wStream = new wstringstream();
			DynamicArray<wstring>* parts = new DynamicArray<wstring>();
			//database에 저장
			for (int i = 0; i < wList.size()-1; i++)
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
			cout << "최근 저장 파일 불러오기 완료" << endl;
			//해제
			_iFile->close();
			delete wStream;
			delete parts;

			return true;

			break;
		}
		case Gsys::E_LoadType::LOAD_BIN:
		{
			//경로 설정
			string path = MYLOCALPATH_SAVE;
			path.append("save_prev.bin");
			//파일 오픈
			_iFile->open(path);
			//버퍼
			wstring wTemp;
			DynamicArray<wstring> wList;
			//개행 읽기
			while (std::getline(*_iFile, wTemp))
			{
				wList.push_back(wTemp);
			}
			//split 버퍼
			wstringstream* wStream = new wstringstream();
			DynamicArray<wstring>* parts = new DynamicArray<wstring>();
			//database에 저장
			for (int i = 0; i < wList.size() - 1; i++)
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
			cout << "최근 저장 파일 불러오기 완료" << endl;
			//해제
			_iFile->close();
			delete wStream;
			delete parts;

			return true;

			break;
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
			//파일 오픈
			_iFile->open(path);
			//버퍼
			wstring wTemp;
			DynamicArray<wstring> wList;
			//개행 읽기
			while (std::getline(*_iFile, wTemp))
			{
				wList.push_back(wTemp);
			}
			//split 버퍼
			wstringstream* wStream = new wstringstream();
			DynamicArray<wstring>* parts = new DynamicArray<wstring>();
			//database에 저장
			for (int i = 0; i < wList.size() - 1; i++)
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
			cout << "최근 저장 파일 불러오기 완료" << endl;
			//해제
			_iFile->close();
			delete wStream;
			delete parts;

			return true;

			break;
		}
		case Gsys::E_LoadType::LOAD_BIN:
		{
			//경로 설정
			string path = MYLOCALPATH_SAVE;
			path.append(fName);
			path.append(".bin");
			//파일 오픈
			_iFile->open(path);
			//버퍼
			wstring wTemp;
			DynamicArray<wstring> wList;
			//개행 읽기
			while (std::getline(*_iFile, wTemp))
			{
				wList.push_back(wTemp);
			}
			//split 버퍼
			wstringstream* wStream = new wstringstream();
			DynamicArray<wstring>* parts = new DynamicArray<wstring>();
			//database에 저장
			for (int i = 0; i < wList.size() - 1; i++)
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
			cout << "최근 저장 파일 불러오기 완료" << endl;
			//해제
			_iFile->close();
			delete wStream;
			delete parts;

			return true;

			break;
		}
		}
		break;
	}
	}


	return false;
}

sData CreateLoadData(DynamicArray<wstring>* list)
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

std::wstring CreateDataLine(const Info<sData>* iData)
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
