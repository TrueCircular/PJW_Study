#pragma once
#include "TBasisLib.h"
#include "TCamera.h"
#include "map/TMap.h"
#include "TEditer.h"
class Sample : public TBasisLib
{
public:
	TMap			m_CustomMap;
	TCamera* m_pMainCamera;
	TLineShape		m_LineDraw;
	TEditer			m_ShaderEditer;
public:
	bool		Init();
	bool		Frame();
	bool		Render();
	bool		Release();
	bool		DrawDebug();
	int			WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	//--------------------------------------------------------------------------------------
	// 변경된 클라이언트 영역를 재설정을 위한 소멸 및 생성
	//--------------------------------------------------------------------------------------
	HRESULT		CreateResource();
	HRESULT		DeleteResource();
public:
	Sample(void);
	virtual ~Sample(void);
};
