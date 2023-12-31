#pragma once
#include "TCore.h"
#include "TSpriteObj.h"
#include "TSoundMgr.h"

using SPRITE_OBJ = std::shared_ptr<TSpriteTexture>;

class Sample : public TCore
{
	TPlaneObj* main;
	TSound* music;
	std::vector<SPRITE_OBJ> bird;

	float gradation = 0;
	bool _isBack = false;
public:
	bool Init()override;
	bool Frame()override;
	bool Render()override;
	bool Release()override;
};

