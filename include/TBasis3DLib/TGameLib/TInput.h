#pragma once
#include "TStd.h"
enum KeyState
{
	KEY_FREE = 0,
	KEY_UP,
	KEY_PUSH,
	KEY_HOLD,
};
class TInput : public TSingleton<TInput>
{
	friend class TSingleton<TInput>;
private:
	DWORD  m_dwKeyState[256]; // 256 Ű
public:
	POINT  m_ptPos;
public:
	bool	Init();
	bool	Frame();
	bool	Release();
	DWORD   GetKey(DWORD dwKey);
private:
	TInput();
public:
	virtual ~TInput();
};
#define I_Input TInput::GetInstance()

