#include "Sample.h"

float g_fMapHalfSizeX = 800;
float g_fMapHalfSizeY = 450;

bool Sample::Init()
{
    main = new TPlaneObj;
    main->Set(m_pDevice, m_pImmediateContext);
    main->SetPos({ 0,0,0, });
    main->SetScale({ g_fMapHalfSizeX, g_fMapHalfSizeY, 1.0f });
    main->Create(L"../../resource/Background/Main.png", L"../../resource/shader/Plane.hlsl");

    m_pMainCamera->Create({ 0,0,0 }, { (float)g_dwWindowWidth, (float)g_dwWindowHeight });

    music = I_Sound.Load(L"../../resource/Sound/Scene/Main.wav");
    music->Play(true);


    return true;
}

bool Sample::Frame()
{
    I_Sound.Frame();
    main->Frame();
    return true;
}

bool Sample::Render()
{
    main->SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matOrthoProjection);
    main->Render();
    return true;
}

bool Sample::Release()
{
    return true;
}


TGAME("ssda", 1600, 900)
