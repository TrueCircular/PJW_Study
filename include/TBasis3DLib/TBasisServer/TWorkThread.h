#pragma once
#include "TThread.h"

class TWorkThread : public TThread
{
public:
	bool		m_bLoop;
public:
	bool		Run();
public:
	TWorkThread(void);
	virtual ~TWorkThread(void);
};
