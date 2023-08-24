#include "Sample.h"
float g_fMapHalfSizeX = 800;
float g_fMapHalfSizeY = 450;

bool Sample::Init()
{
	m_pMapObj = new TPlaneObj;
	m_pMapObj->Set(m_pDevice, m_pImmediateContext);
	m_pMapObj->SetPos({ 0.0f,0.0f ,0.0f });
	m_pMapObj->SetScale(TVector3(g_fMapHalfSizeX, g_fMapHalfSizeY, 1.0f));
	m_pMapObj->Create(L"../../resource/map01.png", L"../../resource/shader/Plane.hlsl");

	m_MainCamera.Create({ 0.0f,0.0f, 0.0f }, { (float)m_dwWindowWidth, (float)m_dwWindowHeight });
	return true;
}
bool Sample::Frame()
{
	return true;
}
bool Sample::Render()
{
	m_pMapObj->SetMatrix(nullptr, &m_MainCamera.m_matView, &m_MainCamera.m_matOrthoProjection);
	m_pMapObj->Render();
	
	return true;
}
bool Sample::Release()
{
	m_pMapObj->Release();
	delete m_pMapObj;
	return true;
}


TGAME("KGCA", 1600, 900);