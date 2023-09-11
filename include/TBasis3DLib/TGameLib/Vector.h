#pragma once
#include "Vector4.h"
class FMatrix;
class FVector
{
public:
	float X;
	float Y;
	float Z;
	static const FVector ZeroVector;
	FVector operator + (const FVector& v);
	FVector operator - (const FVector& v);
	FVector operator * (const float s);
	bool operator == (const FVector& v);
	bool operator != (const FVector& v);
	// Dot Product
	float operator | (FVector const &v0);
	// Cross Product
	FVector operator ^ (FVector const &v0);
	FVector operator * (const FMatrix& m);
	float Size();
	bool Normalize();
	bool IsNearlyZero(float Tolerance = KINDA_SMALL_NUMBER) const;
public:
	FVector();
	FVector(float x, float y, float z);
	FVector(const FVector& v);
};

