#pragma once
#include "TCore.h"
#include "TSoundMgr.h"
#include "GameObject.h"

using std::shared_ptr;
using std::make_shared;
class Sample : public TCore
{
public:
	shared_ptr<GameObject> _testBackground;
public:
	bool Init()override;
	bool Frame()override;
	bool Render()override;
	bool Release()override;
};

