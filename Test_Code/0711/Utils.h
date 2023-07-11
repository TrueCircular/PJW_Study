#pragma once

struct TPoint
{
	float x;
	float y;
	TPoint(){}
	TPoint(float fx, float fy) :x(fx), y(fy) {}
	
	TPoint operator + (TPoint& p)
	{
		return TPoint(x + p.x, y + p.y);
	}
	TPoint operator - (TPoint& p)
	{
		return TPoint(x - p.x, y - p.y);
	}
	TPoint operator * (float value)
	{
		return TPoint(x * value, y * value);
	}
	TPoint operator / (float value)
	{
		return TPoint(x / value, y / value);
	}
};

class Utils
{
};

