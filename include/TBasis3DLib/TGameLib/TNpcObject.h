#pragma once
#include "TPawn.h"
class TNpcObject : public TPawn
{
public:
	virtual bool	Frame() override;
public:
	TNpcObject();
	virtual ~TNpcObject();
};

