#include "QObject.h"

void QDynamicObject::Move(E_MoveType mType, float second)
{

	if (_position.x < 0.0f ||
		_position.x > 600.0f ||
		_position.y < 0.0f ||
		_position.y > 600.0f ||
		_position.z < 0.0f ||
		_position.z > 600.0f)
	{
		mType = E_MoveType::NONE;
	}

	switch (mType)
	{
	case E_MoveType::MOVE_FORWARD:
	{
		_dir = _dirArray[0];
		break;
	}
	case E_MoveType::MOVE_BACK:
	{
		_dir = _dirArray[1];
		break;
	}
	
	case E_MoveType::MOVE_UP:
	{
		_dir = _dirArray[2];
		break;
	}
	case E_MoveType::MOVE_DOWN:
	{
		_dir = _dirArray[3];
		break;
	}
	case E_MoveType::MOVE_LEFT:
	{
		_dir = _dirArray[4];
		break;
	}
	case E_MoveType::MOVE_RIGHT:
	{
		_dir = _dirArray[5];
		break;
	}
	case E_MoveType::NONE:
	{
		_dir = TPoint3(0, 0, 0);

		cout << "���� �������ϴ�." << endl;
		break;
	}
	default:
		break;
	}

	TPoint3 velocity = _dir * _speed * second;
	_position = _position + velocity;
	_box.Set(_position, _box.s);
}

void QDynamicObject::MoveToTarget(TPoint3& tPos, float second)
{
	//Ÿ������
	_target = tPos;
	TPoint3 tDir = _position - _target;
	//�Ÿ�, ����ȭ
	float dist = Util::GetInstance()->GetLength(tDir);
	tDir = Util::GetInstance()->Normalize(tDir);
	//�̵�
	if (dist > 12.f)
	{
		TPoint3 velocity = tDir * _speed * second;
		_position += velocity;
	}
}

void QObject::SetObject(TPoint3& pos, TPoint3& surface)
{
	_box.Set(pos, surface);
}
