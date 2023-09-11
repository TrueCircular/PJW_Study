#pragma once
#include "TEnemyState.h"
class TStandState :
	public TEnemyState
{
public:
	void Process(TPawn* pPlayer);
	TStandState(TPawn* owner);
};

