#include <iostream>
#include <Windows.h>
#include "TimeManager.h"
#include <thread>

#define TIME_MANAGER TimeManager::GetInstance()

int main()
{
 
    //while (true) 
    //{
    //    TIME_MANAGER->Update();

    //    cout << "GameTime :" << TIME_MANAGER->GetGameTime() << endl;
    //    cout << "DeletaTime :" << TIME_MANAGER->GetDeltaTime() << endl;
    //    cout << "FPS :" << TIME_MANAGER->GetFPS() << endl;
    //}

    shared_ptr<EventTimer> tt = make_shared<EventTimer>();
    tt->Start();
    shared_ptr<EventTimer> tt2 = make_shared<EventTimer>();
    tt2->Start();
    while (true)
    {
        TIME_MANAGER->Update();

        if (TIME_MANAGER->GetGameTime() >= 3.3)
        {
            tt->Stop();
        }
        if (TIME_MANAGER->GetGameTime() >= 4.354)
        {
            tt2->Stop();
            break;
        }
    }
    cout << tt->GetElapsedTime() << endl;
    cout << tt2->GetElapsedTime() << endl;


    //LocalTimeInfo lTime = TIME_MANAGER->GetLocalTimeInfo();

    //cout << lTime._tm.tm_year << "년 " << lTime._tm.tm_mon << "월 " <<
    //    lTime._tm.tm_hour << "시 " << lTime._tm.tm_min << "분 " << endl;

	return 0;
}