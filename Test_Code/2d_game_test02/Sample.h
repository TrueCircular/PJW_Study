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
	shared_ptr<GameObject> _testObject;
	shared_ptr<GameObject> _testSpriteObj;
	shared_ptr<GameObject> _testNomalSpriteObj;
	float _time = 0;
	bool _isCamMove = false;

public:
	bool Init()override;
	bool Frame()override;
	bool Render()override;
	bool Release()override;
};

