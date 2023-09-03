#include "Sample.h"
#include "TWriter.h"
#include "ICoreStd.h"

float g_fMapHalfSizeX = 800;
float g_fMapHalfSizeY = 450;

using std::shared_ptr;

bool Sample::Init()
{
	//imageComponent DESC
	S_TOBJECT_DESC iInfo;
	iInfo.pos = { 0,0,0 };
	iInfo.scale = { g_fMapHalfSizeX ,g_fMapHalfSizeY ,1.0 };
	iInfo.shaderFileName = L"../../resource/shader/Plane.hlsl";
	iInfo.texFileName = L"../../resource/Background/Main.png";
	//Component Set
	shared_ptr<ImageComponent> image = make_shared<ImageComponent>();
	image->Imageload(iInfo);
	//make and AddComponent
	_testBackground = make_shared<GameObject>();
	_testBackground->AddComponent(L"Image", image);
	//_testBackground->AddComponent(L"Image", image); 같은 이름을 가진 컴포넌트를 추가하는것을 허용하지 않음

	//Create Camera
	m_pMainCamera->Create({ 0,0,0 }, { (float)g_dwWindowWidth, (float)g_dwWindowHeight });
	return true;
}

bool Sample::Frame()
{
	_testBackground->Frame();
	return true;
}

bool Sample::Render()
{
	_testBackground->Render();
	return true;
}

bool Sample::Release()
{
	_testBackground->Release();
	return true;
}


TGAME("ssda", 1600, 900)
