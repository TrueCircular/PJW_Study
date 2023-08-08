#include "TWindow.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

bool TWindow::SetRegisterClassWindow(HINSTANCE hInstance)
{
    m_hInstance = hInstance;
    WNDCLASSEXW wcex;
    ZeroMemory(&wcex, sizeof(wcex));
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.hInstance = hInstance;
    wcex.lpszClassName = L"KGCA윈도우";
    wcex.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(255, 255, 255)); //(COLOR_WINDOW + 1);
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);

    WORD ret = RegisterClassExW(&wcex);
    return true;
}

bool TWindow::SetWindow(const WCHAR* szTitle, DWORD dwWindowWidth, DWORD dwWindowHeight)
{
    m_dwWindowWidth = dwWindowWidth;
    m_dwWindowHeight = dwWindowHeight;
#ifndef _DEBUG
    m_dwExStyle = WS_EX_TOPMOST;
    m_dwStyle = WS_POPUPWINDOW;
#else
    m_dwExStyle = WS_EX_APPWINDOW;
#endif // _DEBUG
    m_hWnd = CreateWindowEx(m_dwExStyle, L"KGCA윈도우", szTitle, m_dwStyle,
        m_dwWindowPosX, m_dwWindowPosY, dwWindowWidth, dwWindowHeight, nullptr, nullptr, m_hInstance, nullptr);
    if (!m_hWnd)
    {
        return FALSE;
    }
    ShowWindow(m_hWnd, SW_SHOWNORMAL);
    return true;
}
