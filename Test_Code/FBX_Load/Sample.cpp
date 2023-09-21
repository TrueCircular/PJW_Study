#include "Sample.h"
#include "ICoreStd.h"

float g_fMapHalfSizeX = 400;
float g_fMapHalfSizeY = 300;

bool Sample::Init()
{
	ModelManager::GetInstance()->AddFbxModelData(L"Box", L"../../resource/Fbx/Test/box.FBX");
	ModelManager::GetInstance()->AddFbxModelData(L"Sphere", L"../../resource/Fbx/Test/Sphere.FBX");

	_testBox = make_shared<TObject>();
	_testBox->Set(m_pDevice, m_pImmediateContext);
	_testBox->m_VertexList.resize(ModelManager::GetInstance()->GetFbxModelData(L"Box").size());
	_testBox->m_VertexList = ModelManager::GetInstance()->GetFbxModelData(L"Box");
	_testBox->Create(L"../../resource/topdownmap.jpg", L"../../resource/shader/Plane.hlsl");

	_testSphere = make_shared<TObject>();
	_testSphere->Set(m_pDevice, m_pImmediateContext);
	_testSphere->m_VertexList.resize(ModelManager::GetInstance()->GetFbxModelData(L"Sphere").size());
	_testSphere->m_VertexList = ModelManager::GetInstance()->GetFbxModelData(L"Sphere");
	_testSphere->SetPos({ 40,0,0 });
	_testSphere->SetScale({ 0.15f,0.15f,0.15f });
	_testSphere->Create(L"../../resource/topdownmap.jpg", L"../../resource/shader/Plane.hlsl");

	DebugCameraSet();
	return true;
}

bool Sample::Frame()
{
	_testBox->m_vRotation.y += DegreeToRadian(15) * g_fSecondPerFrame;
	_testBox->UpdateMatrix();

	_testSphere->m_vRotation.y += DegreeToRadian(15) * g_fSecondPerFrame;
	_testSphere->UpdateMatrix();
	return true;
}

bool Sample::Render()
{
	_testBox->SetMatrix(nullptr, &ICore::g_pMainCamera->m_matView, &ICore::g_pMainCamera->m_matPerspectiveProj);
	_testBox->Render();

	_testSphere->SetMatrix(nullptr, &ICore::g_pMainCamera->m_matView, &ICore::g_pMainCamera->m_matPerspectiveProj);
	_testSphere->Render();

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
