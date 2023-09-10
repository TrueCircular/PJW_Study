#include "Sample.h"
#include "TWriter.h"
#include "ICoreStd.h"
#include "TInput.h"
float g_fMapHalfSizeX = 800;
float g_fMapHalfSizeY = 450;

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

bool Sample::Init()
{
	_backGround = make_shared<GameObject>();
	_backGround->Init();
	_image = make_shared<ImageComponent>();

	_backGround->SetScale({ (float)g_dwWindowWidth / 2, (float)g_dwWindowHeight / 2, 1 });
	_backGround->AddComponent(L"Image", _image);
	TileManager::GetInstance().CreateRectTileMap(_backGround->m_vScale, 80, 50);


	S_TOBJECT_DESC map;
	map.shaderFileName = L"../../resource/shader/Plane.hlsl";
	map.texFileName = L"../../resource/Map/WorldMap.png";
	_image->Imageload(map);

	//Create Camera
	m_pMainCamera->Create({ 0,0,0 }, { (float)g_dwWindowWidth, (float)g_dwWindowHeight });
	return true;
}

bool Sample::Frame()
{
	_backGround->Frame();
	TileManager::GetInstance().Frame();

	DebugMode();
	return true;
}

bool Sample::Render()
{
	_backGround->Render();

	TileManager::GetInstance().Render();
	return true;
}

bool Sample::Release()
{
	_backGround->Release();
	return true;
}

TGAME("ssda", 1600, 900)
