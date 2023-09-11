#pragma once
#include "TStd.h"
struct TShpere
{
	float fRadius;
	FVector vCenter;
};
class TCollision
{
public:
	static bool RectInPt(RECT rt1, POINT pt);
	static bool RectToRect(RECT rt1, RECT rt2);
	static bool SphereToPt(TShpere s, FVector pt);
};

