#include "Sample.h"
#include "TWriter.h"
#include "ICoreStd.h"

float g_fMapHalfSizeX = 400;
float g_fMapHalfSizeY = 300;

using std::shared_ptr;

bool Sample::Init()
{

	_map = new TMap;

	_map->Set(m_pDevice, m_pImmediateContext);
	_map->CreateHeightMap(L"../../resource/topdownmap.jpg");
	_map->LoadHightMap(L"../../resource/shader/Plane.hlsl", L"../../resource/topdownmap.jpg");

	m_pMainCamera->CreateLookAt({ 0,512,-512.f }, { 0,0,1 });
	m_pMainCamera->CreatePerspectiveFov(T_PI * 0.25, (float)g_dwWindowWidth / (float)g_dwWindowHeight,
		1.0f, 10000.0f);
	return true;
}

bool Sample::Frame()
{
	return true;
}

bool Sample::Render()
{
	_map->SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matPerspectiveProj);
	_map->Render();
	return true;
}

bool Sample::Release()
{
	_map->Release();
	delete _map;
	return true;
}


TGAME("ssda", 1600, 900)
