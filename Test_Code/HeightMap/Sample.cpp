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

	m_pMainCamera->CreateLookAt({ 0,408.f,-469.5f }, { 0,0,1 });
	//m_pMainCamera->CreateLookAt({ 0,100.f,-150.f }, { 0,0,0 });

	m_pMainCamera->CreatePerspectiveFov(T_PI * 0.25, (float)g_dwWindowWidth / (float)g_dwWindowHeight,
		1.0f, 10000.0f);
	return true;
}

bool Sample::Frame()
{
	DebugMode();
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

void Sample::DebugMode()
{
	if (I_Input.GetInstance().m_dwKeyState[VK_NUMPAD4] == KEY_PUSH)
	{
		m_rsFillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
	}
	if (I_Input.GetInstance().m_dwKeyState[VK_NUMPAD5] == KEY_PUSH)
	{
		m_rsFillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
	}
}
TGAME("ssda", 1600, 900)
