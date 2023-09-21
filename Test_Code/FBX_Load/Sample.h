#pragma once
#include "TCore.h"
#include "TObject.h"
#include "TDebugCamera.h"
#include "ModelManager.h"

using std::shared_ptr;
using std::make_shared;

class Sample : public TCore
{
public:
	shared_ptr<TObject>		 _testBox;
	shared_ptr<TObject>		 _testBox2;

	shared_ptr<TDebugCamera> _debugCamera;
public:
	bool Init()override;
	bool Frame()override;
	bool Render()override;
	bool Release()override;
public:
	bool  DeleteDxResource() override;
	bool  CreateDxResource() override;
private:
	void DebugCameraSet();
};

