#pragma once
#include "Vector.h"


// Generic axis enum (mirrored for property use in Object.h)
namespace EAxis
{
	enum Type
	{
		None,
		X,
		Y,
		Z,
	};
}


// Extended axis enum for more specialized usage
namespace EAxisList
{
	enum Type
	{
		None = 0,
		X = 1,
		Y = 2,
		Z = 4,

		Screen = 8,
		XY = X | Y,
		XZ = X | Z,
		YZ = Y | Z,
		XYZ = X | Y | Z,
		All = XYZ | Screen,

		//alias over Axis YZ since it isn't used when the z-rotation widget is being used
		ZRotation = YZ,

		// alias over Screen since it isn't used when the 2d translate rotate widget is being used
		Rotate2D = Screen,
	};
}

struct float4x4
{
	union {
		struct {
			float _11, _12, _13, _14;
			float _21, _22, _23, _24;
			float _31, _32, _33, _34;
			float _41, _42, _43, _44;
		};
		float M[4][4];
	};
};
class FMatrix : public float4x4
{
public:
	FMatrix operator* (const FMatrix& m) const;
public:
	void SetIdentity();//단위행렬
	static const FMatrix Identity;
	//이동행렬
	void Translation(const FVector &vector);
	void Translation(float x, float y, float z);
	//신축행렬
	void Scale(const FVector &vector);
	void Scale(float x, float y, float z);
	// 회전행렬
	void XRotate(float fRadian);
	void YRotate(float fRadian);
	void ZRotate(float fRadian);
	FMatrix Transpose();// 전치행렬
	float Determinant() const;
	FMatrix Inverse() const;
	FVector GetScaledAxis(EAxis::Type Axis) const;
public:
	FMatrix();
	FMatrix(FVector4 row1, FVector4 row2, FVector4 row3, FVector4 row4);
	FMatrix(const FMatrix& matrix);
	~FMatrix();
};

