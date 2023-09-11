#pragma once
#include "TPawn.h"
struct TEffectInfo: public TPawn
{
	virtual void    BeginOverlap(TPawn* pDeskObj, DWORD dwState);

	int  m_iSpriteIndex=0;
	float m_fSpriteTimer = 0.0f;
	int   iMaxSprite = 0;
	bool  Frame()
	{
		m_fLifeTime -= g_fSecPerFrame;
		if (m_fLifeTime <= 0.0f)
		{
			m_bDead = true;
		}
		m_fSpriteTimer += g_fSecPerFrame;
		float fStep = 1.0f / iMaxSprite;
		if (m_fSpriteTimer >= fStep)
		{
			m_iSpriteIndex++;
			if (m_iSpriteIndex >= iMaxSprite) m_iSpriteIndex = 0;
			m_fSpriteTimer -= fStep;
		}
		m_Position = m_Position + m_Direction * g_fSecPerFrame* m_fSpeed;
		SetPos(m_Position);
		return true;
	}
};
class TEffectObject : public TPawn
{
public:
	std::vector<RECT> m_rtlist;
	
	std::list< TEffectInfo>  m_List;
public:
	bool Frame() override;
	bool Render() override;
public:
	TEffectObject();
	virtual ~TEffectObject();
};

