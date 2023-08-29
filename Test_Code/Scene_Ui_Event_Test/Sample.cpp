#include "Sample.h"


float g_fMapHalfSizeX = 400;
float g_fMapHalfSizeY = 300;

bool Sample::Init()
{
    //main->Set(m_pDevice, m_pImmediateContext);
    //main->SetPos(TVector3(0, 0, 0));
    //main->SetScale(TVector3(g_fMapHalfSizeX, g_fMapHalfSizeY, 1));
    //main->Create(L"../../resource/Background/Main.png", L"../../resource/shader/Plane.hlsl");


    //m_pMainCamera->Create(TVector3(0, 0, 0), TVector2((float)m_dwWindowWidth, (float)m_dwWindowHeight));
    return true;
}

bool Sample::Frame()
{
   
    return true;
}

bool Sample::Render()
{
    return true;
}

bool Sample::Release()
{
    return true;
}


TGAME("ssda", 1600, 900)
