#pragma once
#include "TPawn.h"

class TUIObject : public TPawn
{

public:
	void SetMatrix(FMatrix* world,FMatrix* view, FMatrix* proj) override;
	bool Frame() override;
	bool LoadTexture(std::wstring loadfile, std::wstring loadMaskfile) override;
public:
	TUIObject();
	virtual ~TUIObject();
};

