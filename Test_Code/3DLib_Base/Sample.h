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
	// ����� Ŭ���̾�Ʈ ������ �缳���� ���� �Ҹ� �� ����
	//--------------------------------------------------------------------------------------
	HRESULT		CreateResource();
	HRESULT		DeleteResource();
public:
	Sample(void);
	virtual ~Sample(void);
};
