#pragma once
#include "TCore.h"
#include "TPlaneObj.h"

class Sample : public TCore
{
	TObject* m_pMapObj = nullptr;
	ID3D11BlendState* m_AlphaBlend = nullptr;

public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
public:
	void  CreateBlendState();

};

