#pragma once
#include "TPawn.h"
class THeroObject : public TPawn
{
public:
	bool Frame() override;
public:
	THeroObject();
	virtual ~THeroObject();
};

