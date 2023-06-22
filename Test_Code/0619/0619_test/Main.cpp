// 0619_test.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include <fstream>
#include <iostream>
#include <string.h>
#include <sstream>
#include <locale>
using namespace std;

struct savenumber
{
    int a = 10;
    int b = 20;
    int c = 30;
    wstring talk = L"안녕이다\n";
};

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
	void pop_back(const T& data);
	int size() { return _size; }

	T& operator[](int index) { return this->_array[index]; }
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



int main()
{
    std::locale::global(std::locale("Korean"));
    wifstream iFile;
    wofstream oFile;
    savenumber sv;

 //   wstring write = to_wstring(sv.a);
 //   write += L",";
 //   write += to_wstring(sv.b);
 //   write += L",";
 //   write += to_wstring(sv.c);
 //   write += L",";
 //   write += sv.talk;

	//oFile.open("hiTest.bin", ios::binary);
	//oFile.write(write.c_str(), write.size());
	//oFile.close();

	sv.a = 100;
	sv.b = 200;
	sv.c = 300;
	sv.talk = L"안녕못하다";

	wstring write2 = to_wstring(sv.a);
	write2 += L",";
	write2 += to_wstring(sv.b);
	write2 += L",";
	write2 += to_wstring(sv.c);
	write2 += L",";
	write2 += sv.talk;
	write2 += L"\n";

    //oFile.open("hiTest.txt");
    //oFile.write(cWrite->c_str(), writeSize);
    //oFile.close();
	oFile.open("hiTest.txt");
	oFile.write(write2.c_str(), write2.size());
	oFile.write(write2.c_str(), write2.size());
	oFile.close();

	wstring tRead;

	wchar_t* readbuffer = new wchar_t();
    iFile.open("hiTest.txt");
	while (iFile.getline(readbuffer, write2.size()))
	{
		wcout << readbuffer << endl;
	}
    //wchar_t* cread = new wchar_t[writeSize * 100];
	


	//while (std::getline(iFile, tRead))
	//{
	//	wcout << tRead << endl;
	//}
	iFile.close();


 //   wstring one = cWrite->substr(), temp;
	//DynamicArray<wstring> parts;
 //   wstringstream wss(one);

	//while (std::getline(wss, temp, L','))
	//{
	//	parts.push_back(temp);
	//}
	//int tA = stoi(parts[0]);
	//int tB = stoi(parts[1]);
	//int tC = stoi(parts[2]);
	//wstring tD = parts[3];

	//savenumber wow;
	//wow.a = tA;
	//wow.b = tB;
	//wow.c = tC;
	//wow.talk = tD;

	////wcout << wow.a << " " << wow.b << " " << wow.c << " " << wow.talk;

	//wchar_t* frint = new wchar_t[writeSize * 100];

	//while (iFile.getline(frint, writeSize * 100))
	//{
	//	wcout << frint << endl;
	//}

}
