#pragma once
#include "TCore.h"
#include "TSoundMgr.h"
#include "GameObject.h"

class Sample : public TCore
{
public:
	std::shared_ptr<GameObject> _testBackground;
	std::shared_ptr<ImageComponent> image;
public:
	bool Init()override;
	bool Frame()override;
	bool Render()override;
	bool Release()override;
};

