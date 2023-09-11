#pragma once
#include "TPawn.h"
#include "TFiniteState.h"
class TEnemyState
{
public:
	TPawn*    m_pOwner;
	DWORD		m_dwState;
	float		m_fTimer;
	float		m_fTransitionInterval;
public:
	virtual void Process(TPawn* pPlayer) = 0;
	TEnemyState(TPawn* owner);
};

