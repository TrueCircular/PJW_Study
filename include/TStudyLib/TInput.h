#pragma once
#include "TStd.h"
enum KeyState
{
    KEY_FREE = 0,
    KEY_UP = 1,
    KEY_PUSH = 2,
    KEY_HOLD = 3,
};
class TInput
{
public:
    POINT     m_MousePos;
    POINT     m_BeforeMousePos;
    TVector3  m_vOffset = { 0,0,0 };
    DWORD     m_dwKeyState[256];
public:
    bool  Init();
    bool  Frame();
    bool  Render();
    bool  Release();
    TVector3 GetWorldPos(TVector2 vWindow, TVector3 vCamera);
    TVector2 GetWorldPosVec2(TVector2 vWindow, TVector3 vCamera);
public:
    static TInput& GetInstance()
    {
        static TInput input;
        return input;
    }
    DWORD Getkey(DWORD key)
    {
        return m_dwKeyState[key];
    }
private:
    TInput() {};
public:
    ~TInput() {}
};

#define I_Input TInput::GetInstance()