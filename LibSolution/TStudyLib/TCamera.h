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
    TVector3   m_vLook;
    TVector3   m_vUp;
    TVector3   m_vSide;
    float      m_fSpeed = 10.0f;
    float      m_near = 0.1f;
    float      m_far = 1000.f;
public:
    TMatrix                 m_matView;
public:
    TMatrix                 m_matOrthoProj;
    TMatrix                 m_matPerspectiveProj;
public:
    TVector3                m_vCameraPos;
    TVector3                m_vTargetPos;

    DWORD                   m_dwWindowWidth;
    DWORD                   m_dwWindowHeight;
    E_CameraZoomState       m_zoomState = E_CameraZoomState::CAMERA_ZOOM_ONCE;
protected:
    void      UpdateVector();
public:
    virtual bool  Init();
    virtual bool  Frame();
    virtual bool  Render();
    virtual bool  Release();
public:
    TMatrix  CreateLookAt(TVector3 pos, TVector3 target, TVector3 up = { 0,1,0 });
    TMatrix  CreatePerspectiveFov(float fFov, float fAspect, float fNear, float fFar);
};

