#pragma once
#include "TWindow.h"
#include "TImageManager.h"
#include "TSoundManager.h"
#include "TInput.h"
#include "TGraphics.h"
#include "TTimer.h"
#include "TWriter.h"
#include "TCamera.h"
class TGameCore : public TWindow
{
public:
	TGraphics   m_Graphics;
	TTimer		m_Timer;
	TCamera		m_Camera;
public:
	bool  GameInit()override;
	bool  GameRun() override;
	bool  GameRelease() override;
	// 초기화
	virtual bool Init();
	// 실시간 계산
	virtual bool PreFrame();	
	virtual bool Frame();
	virtual bool PostFrame();
	// 실시간 드로우
	virtual bool PreRender();
	virtual bool Render();
	virtual bool PostRender();
	// 소멸
	virtual bool Release();
public:
	TGameCore();
	virtual ~TGameCore();
};

