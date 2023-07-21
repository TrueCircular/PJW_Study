#include "QObject.h"

void QDynamicObject::SetTarget(TPoint3& tPos)
{
}

void QDynamicObject::Move(E_MoveType mType, float second)
{
}

void QDynamicObject::MoveToTarget(TPoint3& tPos, float second)
{
}

void QObject::SetObject(TPoint3& pos, TPoint3& surface)
{
	_box.Set(pos, surface);
}
