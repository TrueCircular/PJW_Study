#pragma once
#include "TCore.h"
#include "TSoundMgr.h"
#include "GameObject.h"
#include "TileManager.h"

using std::shared_ptr;
using std::make_shared;
class Sample : public TCore
{
public:
	shared_ptr<GameObject>		_backGround;
	shared_ptr<GameObject>		_bird;
	shared_ptr<ImageComponent>	_image;

public:
	void DebugMode();
public:
	bool Init()override;
	bool Frame()override;
	bool Render()override;
	bool Release()override;
};

