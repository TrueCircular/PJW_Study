#pragma once
#include "TStd.h"
#pragma comment(lib, "Winmm.lib")
class TTimer
{
public:
	float   m_fGameTime;		// �� �÷��� �ð�
	float   m_fSecondPerFrame;  // 1�������� ����ð�
	int		m_iFPS;				// 1�ʴ� ������ ī����
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

