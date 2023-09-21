#pragma once
#include "TPlaneObj.h"

class UiObject : public TPlaneObj
{
public:
	virtual void MouseOverlap(TVector2 mPos, DWORD);
};

