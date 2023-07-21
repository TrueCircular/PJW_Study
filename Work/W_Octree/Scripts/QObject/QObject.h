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
	virtual void SetObject(TPoint3& pos, TPoint3& surface) = 0;
	virtual void SetTarget(TPoint3& tPos) = 0;
	virtual void move(E_ObjectType oType, E_MoveType mType, float second) = 0;
};

class QStaticObject : public QObject
{
public:
	void move(E_ObjectType oType, E_MoveType mType, float second) override;
};

class QDynamicObject : public QObject
{
private:
	float _speed;
	TPoint3 _dir;
	TPoint3 _target;
public:
	void SetTarget(TPoint3& tPos) override;
	void move(E_ObjectType oType, E_MoveType mType, float second)override;

};

