#pragma once
#include "TStd.h"
#include <mutex>
struct TMsg
{
	RECT	rt;
	wstring msg;
};
class TWrite : public TSingleton<TWrite>
{
public:
	HFONT	m_hFont;	
	std::vector<TMsg> m_TextList;
	std::mutex      m_hMutex;
public:
	virtual void   push(TMsg msg);
	virtual void   Draw(POINT pos, wstring msg, DWORD color= RGB(255, 0,0));
	virtual void   Draw(int x, int y, wstring msg, DWORD color = RGB(255, 0, 0));
public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
public:
	TWrite();
	virtual ~TWrite();
};
#define g_Write TWrite::GetInstance()

