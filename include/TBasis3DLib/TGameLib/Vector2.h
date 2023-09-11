#pragma once
#include <math.h>
#define PI 					(3.1415926535897932f)	/* Extra digits if needed: 3.1415926535897932384626433832795f */
#define SMALL_NUMBER		(1.e-8f)
#define KINDA_SMALL_NUMBER	(1.e-4f)
#define BIG_NUMBER			(3.4e+38f)
#define EULERS_NUMBER       (2.71828182845904523536f)
#define UE_GOLDEN_RATIO		(1.6180339887498948482045868343656381f)	/* Also known as divine proportion, golden mean, or golden section - related to the Fibonacci Sequence = (1 + sqrt(5)) / 2 */
#define FLOAT_NON_FRACTIONAL (8388608.f) /* All single-precision floating point numbers greater than or equal to this have no fractional value. */


class FVector2
{
public:
	float X;
	float Y;
	static const FVector2 ZeroVector;
	FVector2 operator + (const FVector2& v);
	FVector2 operator - (const FVector2& v);
	FVector2 operator * (const float s);
	bool operator == (const FVector2& v);
	bool operator != (const FVector2& v);
	float Size();
	bool Normalize();
public:
	FVector2();
	FVector2(float x, float y);
	FVector2(const FVector2& v);
};

