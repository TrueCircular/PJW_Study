#pragma once
#include "../Utils.h"

class QObject
{
public:
	int				_nodeIndex = 0;
	wstring			_name;
	TPoint3			_position;
	TPoint3			_prevPos;
	TPoint3			_target;
	TBox			_box;
	bool			_isCollision = false;
	E_ObjectType	_oType;
public:
	QObject() : _name(L""), _oType(E_ObjectType::NONE) {}
	virtual ~QObject() {}
public:
	void SetObject(TPoint3& pos, TPoint3& surface);
	bool Collision(TBox& compare);
	virtual void Move(E_MoveType mType, float second) = 0;
	virtual void MoveToTarget(TPoint3& tPos, float second) = 0;
};

class QStaticObject : public QObject
{
public:
	QStaticObject()
	{
		_oType = E_ObjectType::OBJECT_STATIC;
	}
	virtual void Move(E_MoveType mType, float second) {}
	virtual void MoveToTarget(TPoint3& tPos, float second) {}
};

class QDynamicObject : public QObject
{
private:
	float _speed;
	TPoint3 _dir;
	TPoint3 _dirArray[6];
private:
	bool CollisionCheck();
public:
	QDynamicObject()
	{
		_speed = 10.0f;
		_dirArray[0] = { 0,0,1 };
		_dirArray[1] = { 0,0,-1 };
		_dirArray[2] = { 0,1,0 };
		_dirArray[3] = { 0,-1,0 };
		_dirArray[4] = { -1,0,0 };
		_dirArray[5] = { 1,0,0 };
		_oType = E_ObjectType::OBJECT_DYNAMIC;
	}
public:
	void Move(E_MoveType mType, float second) override;
	void MoveToTarget(TPoint3& tPos, float second) override;
};

