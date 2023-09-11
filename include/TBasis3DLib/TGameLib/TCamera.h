#pragma once
#include "TPawn.h"
class TCamera
{
public:
	FVector m_vPos = { 0.0f,0,-10.0f };
	FVector m_vTarget = { 0,0,100.0f };
	FVector m_vUp = { 0,1,0 };
	FMatrix m_matView;
	FMatrix m_matProj;
	void  Update();
	void CreateView(FVector vPos,
		FVector vTarget, FVector vUp);
	void CreateOrthoProj(float w, float h, float fNear, float fFar);
public:
	TCamera();
	virtual ~TCamera();
};

