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
    TMatrix                 m_matViewinverse;
public:
    TMatrix                 m_matOrthoProjection;
    TMatrix                 m_matOrthoProjectionInverse; 
    TMatrix                 m_matPerspectiveProj;
public:
    TVector3                m_vCameraPos;
    TVector3                m_vTargetPos;

    DWORD                   m_dwWindowWidth;
    DWORD                   m_dwWindowHeight;
    E_CameraZoomState       m_zoomState = E_CameraZoomState::CAMERA_ZOOM_ONCE;
    TRect                   m_rt;
    std::pair<float, float> ProjecPair;

    float m_Near;
    float m_Far;
    float m_cameraMoveSpeed = 400.f;
    bool  _isCamMove = false;
public:
    bool  Init();
    bool  Frame();
    bool  Render();
    bool  Release();
public:
    TMatrix CreateLookAt(TVector3 pos, TVector3 target, TVector3 up = { 0,1,0 });
    TMatrix   CreatePerspectiveFov(float fFov, float fAspect, float fNear, float fFar);
public:
    std::pair<float, float> ZoomInOut(float halfWidth, float halfHeight);
};

