// 0619_test.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include <fstream>
#include <iostream>
#include <string>
#include <locale>
using namespace std;

struct savenumber
{
    int a = 10;
    int b = 20;
    int c = 30;
};


int main()
{
    std::locale::global(std::locale("Korean"));

    wofstream oFile;

    wstring what = L"";
    what = what + L"하이 ";
    oFile.open("good.txt");
    oFile << what << L"불만있다.\n";
    oFile << L"아닌가";
    oFile.close();

    wifstream rFile;
    wstring* si = new wstring;
    *si = L"";
    rFile.open("good.txt");
    
    //wcout << *si << endl;

    if (rFile.is_open())
    {
        while (getline(rFile, *si))
        {
            wcout << *si << endl;
        }
        rFile.close();
        delete si;
    }
    else
    {
        cout << "실패" << endl;
    }

    //std::cout << "Hello World!\n";
}
