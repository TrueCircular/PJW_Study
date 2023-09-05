#pragma once
#include "TStd.h"

enum E_CameraZoomState
{
    CAMERA_ZOOM_ONCE,
    CAMERA_ZOOM_TWICE,
    CAMERA_ZOOM_TRIPLE,
    CAMERA_ZOOM_NONE
};

class TCamera
{
public:
    TMatrix                 m_matView;
    TMatrix                 m_matOrthoProjection;
    TVector3                m_vCameraPos;
    TVector3                m_vCameraMovePos;
    DWORD                   m_dwWindowWidth;
    DWORD                   m_dwWindowHeight;
    E_CameraZoomState       m_zoomState = E_CameraZoomState::CAMERA_ZOOM_ONCE;
    TRect                   m_rt;

    float m_zoomX = 0;
    float m_zoomY = 0;
    float m_cameraMoveSpeed = 400.f;
public:
    bool  Init();
    bool  Frame();
    bool  Render();
    bool  Release();
public:
    bool  Create(TVector3 vPos, TVector2 size);
    std::pair<float,float>  ZoomInOut(float halfWidth, float halfHeight);
};

