#pragma once
#include "TCore.h"
#include "TMap.h"
#include "TQuadTree.h"
#include "TDebugCamera.h"

using std::shared_ptr;
using std::make_shared;
class Sample : public TCore
{
	TMap* _map;
	TQuadTree _qTree;
	shared_ptr<TDebugCamera> _debugCamera;
public:
	float _time = 0;
public:
	bool Init()override;
	bool Frame()override;
	bool Render()override;
	bool Release()override;
public:
	bool  DeleteDxResource() override;
	bool  CreateDxResource() override;
};

