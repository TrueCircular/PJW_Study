#pragma once
#include "TStd.h"
#include "TObject.h"
class TShape : public TObject
{
public:
	bool			Create(S_TOBJECT_DESC desc) override;
};

class TLineShape : TShape
{
public:
};