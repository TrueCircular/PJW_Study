#pragma once
#include "TStd.h"
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#pragma comment( lib, "d2d1.lib" )
#pragma comment( lib, "dwrite.lib" )

struct TTextMsg
{
	float fTimer;
	RECT rt;
	std::wstring text;
	D2D1::ColorF color;
};
class TWriter : public TSingleton<TWriter>
{
	// 窜老按眉 积己(教臂沛)
	static TWriter g_Write;
	TWriter() {};
public:
	virtual ~TWriter() {}
	static TWriter& Get()
	{
		return g_Write;
	}
	std::vector<TTextMsg> m_TextList;
	std::vector<TTextMsg> m_MsgList;
public:
	std::wstring		   m_szDefaultMsg;
public:
	// d2d
	ID2D1Factory*       m_pD2DFactory = nullptr;
	ID2D1RenderTarget*  m_pRT = nullptr;
	///dwrite
	IDWriteFactory*		m_WriteFactory = nullptr;
	IDWriteTextFormat*  m_pTextFormat = nullptr;

	ID2D1SolidColorBrush*	m_pBlackBrush;
public:
	bool	Init();
	bool	Frame();
	bool	Update(IDXGISurface *dxgiSurface);
	bool	Render();
	bool    Release();
	bool	DrawText(POINT pos, const TCHAR* text, D2D1::ColorF color,float fTimer=1.0f);
	bool	DrawMassage(RECT rt, const TCHAR* text, D2D1::ColorF color, float fTimer);
};

