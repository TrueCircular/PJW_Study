#pragma once
#include "TStd.h"
class TCamera
{
public:
    TMatrix                 m_matView;
    TMatrix                 m_matOrthoProjection;
    TVector3                m_vCameraPos;
    TVector3                m_vCameraMovePos;
    DWORD                   m_dwWindowWidth;
    DWORD                   m_dwWindowHeight;
    
    float m_zoomX = 0;
    float m_zoomY = 0;
    float m_cameraMoveSpeed = 300.f;
public:
    bool  Init();
    bool  Frame();
    bool  Render();
    bool  Release();
public:
    bool  Create(TVector3 vPos, TVector2 size);
    void  ZoomInOut();
};

