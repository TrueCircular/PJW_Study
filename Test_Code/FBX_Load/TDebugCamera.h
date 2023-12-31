#pragma once
#include "TCamera.h"
class TDebugCamera : public TCamera
{
public:
    float   m_fCameraYaw = 0.0f;
    float   m_fCameraPitch = 45.0f;
    float   m_fCameraRoll = 0.0f;
public:
    virtual bool Init() override;
    virtual bool Frame()override;
    virtual bool Render()override;
    virtual bool Release()override;
};

