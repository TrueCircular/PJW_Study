#pragma once
#include "TProjectile.h"
#include "TEnemyState.h"
class TAttackState :public TEnemyState
{
public:
	void Process(TPawn* pPlayer);
public:
	TAttackState(TPawn* owner);
};

