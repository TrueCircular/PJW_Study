#pragma once
#include"TStd.h"
class TWindow
{
public:
    HINSTANCE   m_hInstance;
    HWND        m_hWnd;
    DWORD       m_dwExStyle = 0;
    DWORD       m_dwStyle = WS_OVERLAPPEDWINDOW;
    DWORD       m_dwWindowPosX = 0;
    DWORD       m_dwWindowPosY = 0;
    DWORD       m_dwWindowWidth = 0;
    DWORD       m_dwWindowHeight = 0;
public:
    bool SetRegisterClassWindow(HINSTANCE hInstance);
    bool SetWindow(const WCHAR* szTitle, DWORD dwWindowWidth, DWORD dwWindowHeight);
public:
    virtual ~TWindow(){}
};

