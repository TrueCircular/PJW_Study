#pragma once
#include "TCore.h"
#include "TSpriteObj.h"
#include "TSoundMgr.h"
#include "GameObject.h"

class Sample : public TCore
{
public:
	GameObject _testBackground;
public:
	bool Init()override;
	bool Frame()override;
	bool Render()override;
	bool Release()override;
};

