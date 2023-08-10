#include "TCore.h"

bool TCore::EngineInit()
{
	TDevice::Init();
	Init();
	return true;
}

bool TCore::EngineFrame()
{
	TDevice::Frame();
	Frame();
	return true;
}

bool TCore::EngineRender()
{
	TDevice::PreRender();
	Render();
	TDevice::PostRender();
	return true;
}

bool TCore::EngineRelease()
{
	Release();
	TDevice::Release();
	return true;
}

bool TCore::Init()
{
	return true;
}

bool TCore::Frame()
{
	return true;
}

bool TCore::Render()
{
	return true;
}

bool TCore::Release()
{
	return true;
}

bool TCore::Run()
{
	EngineInit();

    MSG msg = { 0 };

    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            //game logic Ã³¸®
			if (!EngineFrame() || !EngineRender())
			{
				break;
			}
        }
    }
	EngineRelease();
	return true;
}
