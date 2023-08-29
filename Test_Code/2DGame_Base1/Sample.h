#pragma once
#include "TCore.h"
#include "TPlaneObj.h"
#include "TSoundMgr.h"
class Sample : public TCore
{
	TPlaneObj* main;
	TSound* music;
public:
	bool Init()override;
	bool Frame()override;
	bool Render()override;
	bool Release()override;
};

