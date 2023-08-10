#pragma once
#include "TDevice.h"
class TCore : public TDevice
{
private:
	bool EngineInit();
	bool EngineFrame();
	bool EngineRender();
	bool EngineRelease();
public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;
public:
	bool Run();
};

