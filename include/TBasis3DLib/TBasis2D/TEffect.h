#pragma once
#include "TPawn.h"

class TEffect : public TPawn
{
public:
	std::vector<RECT> m_rtList;
	int		m_iRectIndex;
	float	m_fTimer;
	float	m_fStep;
public:
	void   SetSprite(std::vector<RECT>& list);
	virtual TPawn* Clone() override;
	bool	Init();
	bool	Frame();
public:
	TEffect();
	virtual ~TEffect();
};

