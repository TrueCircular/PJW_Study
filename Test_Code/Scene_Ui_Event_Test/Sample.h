#pragma once
#include "TCore.h"
#include "TPlaneObj.h"

class Sample : public TCore
{
	TPlaneObj* main;
public:
	bool Init()override;
	bool Frame()override;
	bool Render()override;
	bool Release()override;
};

