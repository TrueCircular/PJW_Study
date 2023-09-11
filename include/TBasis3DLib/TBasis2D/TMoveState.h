#pragma once
#include "TEnemyState.h"
class TMoveState :
	public TEnemyState
{
public:
	void Process(TPawn* pPlayer);
	TMoveState(TPawn* owner);
};

