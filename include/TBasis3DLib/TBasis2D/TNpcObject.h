#pragma once

#include "TStandState.h"
#include "TMoveState.h"
#include "TAttackState.h"

class TNpcObject : public TPawn
{
public:
	TEffect*						m_pProjectile;
	std::vector<TProjectileInfo>	m_ProjectileList;
	TEnemyState*					m_pAction;
	std::vector<TEnemyState*>  m_pActionList;
public:
	virtual void FSM();
	virtual void SetTransition(DWORD dwEevnt);
public:
	virtual bool Damage()				override;
	virtual bool Dead()					override;
public:
	virtual TPawn* Clone() override;
	virtual bool Frame() override;
	virtual bool Render() override;
	virtual bool Release() override;
	TNpcObject()
	{
		m_iObjectType = 200;
	}
};

