#pragma once
#include "TCore.h"
#include "TPlaneObj.h"
#include "EffectObj.h"

class Sample : public TCore
{
	TObject* m_pMapObj = nullptr;
	EffectObj* _effect = nullptr;
	ID3D11BlendState* m_AlphaBlend = nullptr;
	TVector3 move;
	float angle = 0;
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
public:
	void  CreateBlendState();
	
};

