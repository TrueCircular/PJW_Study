// DelegateTest.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>
#include <chrono>


using namespace std;

int main()
{
	chrono::steady_clock::time_point start = chrono::steady_clock::now();

	while (true)
	{
		//chrono::steady_clock::time_point end = chrono::steady_clock::now();
		////chrono::duration<double> current = end - start;
		//chrono::duration<double> current = chrono::duration_cast<chrono::milliseconds>(end - start);

		//std::cout << current.count() << endl;

		//auto now = chrono::system_clock::now();
		////time_t end = chrono::system_clock::to_time_t(now);

		//auto mtime = now.time_since_epoch() % 1000;

		//struct tm tm_1;
		//localtime_s(&tm_1, &end);
		//
		//cout << tm_1.tm_year + 1900 << " " << tm_1.tm_mon + 1 << " " << tm_1.tm_mday <<
		//	" " << tm_1.tm_sec << " " << mtime.count() << endl;

		double spf = 0.0;
		double fTime = 0.0;
		double gTime = 0.0;
		double dfps = 0.0;

		double fps = 0;
		int counting = 0;

		chrono::steady_clock::time_point prev = chrono::steady_clock::now();
		chrono::steady_clock::time_point current;
		chrono::duration<double> elapsed;
		while (1)
		{
			current = chrono::steady_clock::now();
			elapsed = chrono::duration_cast<chrono::milliseconds>(current - prev);

			spf = elapsed.count();
			gTime = fTime += spf;
			prev = current;

			dfps += spf;

			fps = dfps / spf;
	
			cout << "SPF :" << spf << endl;
			cout << "Global Time :" << gTime << endl;
			cout << "FPS : " << fps << endl;

			dfps = 0;
		}

	}
}
