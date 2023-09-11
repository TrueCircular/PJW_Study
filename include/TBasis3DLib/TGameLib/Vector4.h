#include "Vector2.h"
class FVector4
{
public:
	float X;
	float Y;
	float Z;
	float W;
	static const FVector4 ZeroVector;
	FVector4 operator + (const FVector4& v);
	FVector4 operator - (const FVector4& v);
	FVector4 operator * (const float s);
	bool operator == (const FVector4& v);
	bool operator != (const FVector4& v);
	float Size();
	bool Normalize();
public:
	FVector4();
	FVector4(float x, float y, float z, float w);
	FVector4(const FVector4& v);
};