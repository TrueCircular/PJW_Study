#include "QObject.h"

bool QDynamicObject::CollisionCheck()
{
	if (_isCollision)
	{
		cout << "��ü�� �浹�߽��ϴ�." << endl;
		return false;
	}

	if (_position.x < 0.f)
	{
		_position.x = 0.f;
		cout << "���� �ε������ϴ�." << endl;
		return false;
	}
	if (_position.x > 600.f)
	{
		_position.x = 600.f;
		cout << "���� �ε������ϴ�." << endl;

		return false;
	}
	if (_position.y < 0.f)
	{
		_position.y = 0.f;
		cout << "���� �ε������ϴ�." << endl;

		return false;
	}
	if (_position.y > 600.f)
	{
		_position.y = 600.f;
		cout << "���� �ε������ϴ�." << endl;
		return false;
	}
	if (_position.z < 0.f)
	{
		_position.z = 0.f;
		cout << "���� �ε������ϴ�." << endl;
		return false;
	}
	if (_position.z > 600.f)
	{
		_position.z = 600.f;
		cout << "���� �ε������ϴ�." << endl;
		return false;
	}

	return true;
}

void QDynamicObject::Move(E_MoveType mType, float second)
{
	switch (mType)
	{
	case E_MoveType::MOVE_FORWARD:
	{
		_dir = _dirArray[0];
		cout << endl;
		cout << "������ �̵��Ͽ����ϴ�." << endl;
		break;
	}
	case E_MoveType::MOVE_BACK:
	{
		_dir = _dirArray[1];
		cout << endl;
		cout << "�ڷ� �̵��Ͽ����ϴ�." << endl;
		break;
	}
	case E_MoveType::MOVE_UP:
	{
		_dir = _dirArray[2];
		cout << endl;
		cout << "���� �̵��Ͽ����ϴ�." << endl;
		break;
	}
	case E_MoveType::MOVE_DOWN:
	{
		_dir = _dirArray[3];
		cout << endl;
		cout << "�Ʒ��� �̵��Ͽ����ϴ�." << endl;
		break;
	}
	case E_MoveType::MOVE_LEFT:
	{
		_dir = _dirArray[4];
		cout << endl;
		cout << "�������� �̵��Ͽ����ϴ�." << endl;
		break;
	}
	case E_MoveType::MOVE_RIGHT:
	{
		_dir = _dirArray[5];
		cout << endl;
		cout << "���������� �̵��Ͽ����ϴ�." << endl;
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

	if (CollisionCheck())
	{
		_box.Set(_position, _box.s);
	}
	

}

void QDynamicObject::MoveToTarget(TPoint3& tPos, float second)
{
	//Ÿ������
	_target = tPos;
	TPoint3 tDir = _position - _target;
	//�Ÿ�, ����ȭ
	float dist = Util::GetInstance()->GetLength(tDir);
	Util::GetInstance()->Normalize(tDir);
	//�̵�
	if (dist > 12.f)
	{
		TPoint3 velocity = tDir * _speed * second;
		_position += velocity;
	}
	else
	{
		cout << "��ǥ�� ���� �߽��ϴ�." << endl;
	}
}

void QObject::SetObject(TPoint3& pos, TPoint3& surface)
{
	_position = pos;
	_box.Set(pos, surface);
}
