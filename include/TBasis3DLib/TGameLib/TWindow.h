#pragma once
#include "TStd.h"

class TWindow
{
public:
	HWND m_hWnd;
	RECT m_rtWindow;
	RECT m_rtClient;
public:
	bool InitWindow(HINSTANCE hInstance,	
					int nCmdShow);
	bool  Run();
	virtual bool  GameInit();
	virtual bool  GameRun();
	virtual bool  GameRelease();
public:
	TWindow();
	virtual ~TWindow();
};

