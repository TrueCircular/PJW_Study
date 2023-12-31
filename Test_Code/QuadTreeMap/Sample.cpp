#include "Sample.h"
#include "ICoreStd.h"

float g_fMapHalfSizeX = 400;
float g_fMapHalfSizeY = 300;

using std::shared_ptr;

bool Sample::Init()
{

	_map = new TMap;

	_map->Set(m_pDevice, m_pImmediateContext);
	_map->CreateHeightMap(L"../../resource/heightMap513.bmp");
	_map->LoadHightMap(L"../../resource/shader/Plane.hlsl", L"../../resource/Map512Color.png");


	_debugCamera = std::make_shared<TDebugCamera>();
	_debugCamera->CreateLookAt({ 0,513.f,-1.0f }, { 0,0,0 });
	_debugCamera->CreatePerspectiveFov(DegreeToRadian(45), g_dwWindowWidth / (float)g_dwWindowHeight,
		1.0f, 10000.f);

	ICore::g_pMainCamera = _debugCamera.get();

	return true;
}

bool Sample::Frame()
{
	return true;
}

bool Sample::Render()
{
	_map->SetMatrix(nullptr, &ICore::g_pMainCamera->m_matView, &ICore::g_pMainCamera->m_matPerspectiveProj);
	_map->Render();
	return true;
}

bool Sample::Release()
{
	_map->Release();
	delete _map;
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


TGAME("ssda", 1600, 900)
