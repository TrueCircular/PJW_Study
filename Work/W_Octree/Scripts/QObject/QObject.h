#pragma once
#include "../Utils.h"

class QObject
{
public:
	wstring _name;
	TPoint3 _position;
	TBox	_box;
public:
	QObject() : _name(L"") {}
	virtual ~QObject() {}
public:
	void SetObject(TPoint3& pos, TPoint3& surface);
	virtual void SetTarget(TPoint3& tPos) = 0;
	virtual void Move(E_MoveType mType, float second) = 0;
	virtual void MoveToTarget(TPoint3& tPos, float second) = 0;
};

class QStaticObject : public QObject
{
};

class QDynamicObject : public QObject
{
private:
	float _speed;
	TPoint3 _dir;
	TPoint3 _target;
	TPoint3 _dirArray[6];
public:
	QDynamicObject()
	{
		_speed = 0.0f;
		_dirArray[0] = { 0,0,1 };
		_dirArray[1] = { 0,0,-1 };
		_dirArray[2] = { 0,1,0 };
		_dirArray[3] = { 0,-1,0 };
		_dirArray[4] = { -1,0,0 };
		_dirArray[5] = { 1,0,0 };
	}
public:
	void SetTarget(TPoint3& tPos) override;
	void Move(E_MoveType mType, float second) override;
	void MoveToTarget(TPoint3& tPos, float second) override;
};

