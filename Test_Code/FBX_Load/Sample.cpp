#include "Sample.h"
#include "ICoreStd.h"

float g_fMapHalfSizeX = 400;
float g_fMapHalfSizeY = 300;

bool Sample::Init()
{


	DebugCameraSet();
	return true;
}

bool Sample::Frame()
{

	return true;
}

bool Sample::Render()
{

	return true;
}

bool Sample::Release()
{

	return true;
}

bool Sample::DeleteDxResource()
{
	TCore::DeleteDxResource();

	return true;
}

bool Sample::CreateDxResource()
{
	ICore::g_pMainCamera->CreatePerspectiveFov(T_PI * 0.25, (float)
		g_dwWindowWidth / (float)g_dwWindowHeight,
		1.0f, 300.0f);

	TCore::CreateDxResource();

	return true;
}

void Sample::DebugCameraSet()
{
	_debugCamera = make_shared<TDebugCamera>();
	_debugCamera->CreateLookAt({ 0,100,-45.0f }, { 0,0,0 });
	_debugCamera->CreatePerspectiveFov(DegreeToRadian(45), g_dwWindowWidth / (float)g_dwWindowHeight,
		1.0f, 10000.f);
	ICore::g_pMainCamera = _debugCamera.get();
}


TGAME("ssda", 1600, 900)
