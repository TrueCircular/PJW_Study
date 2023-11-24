#include <iostream>
#include <Windows.h>
#include "TimeManager.h"

int main()
{

	TIME_MANAGER->Init();
	
	while (true)
	{
		Sleep(10);
		TIME_MANAGER->Update();

		cout << TIME_MANAGER->GetFrameTimer()->GetFPS() << endl;
	}


	return 0;
}