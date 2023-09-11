#pragma once
#include "TStd.h"
#pragma comment(lib, "Winmm.lib")
class TTimer
{
public:
	float   m_fGameTime;		// 총 플레이 시간
	float   m_fSecondPerFrame;  // 1프레임의 경과시간
	int		m_iFPS;				// 1초당 프레임 카운터
	float   m_fBeforeTime;
	int		m_iFpsCount =0;
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
public:
	TTimer();
	virtual ~TTimer();
};

