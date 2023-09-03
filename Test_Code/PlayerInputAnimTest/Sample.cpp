#include "Sample.h"
#include "TWriter.h"
#include "ICoreStd.h"

float g_fMapHalfSizeX = 800;
float g_fMapHalfSizeY = 450;

using std::shared_ptr;

bool Sample::Init()
{
	_testBackground.SetPos({ 100,0,0 });

	S_TOBJECT_DESC iInfo;
	iInfo.pos = { 0,0,0 };
	iInfo.scale = { g_fMapHalfSizeX ,g_fMapHalfSizeY ,1.0 };
	iInfo.shaderFileName = L"../../resource/shader/Plane.hlsl";
	iInfo.texFileName = L"../../resource/Background/Main.png";

	shared_ptr<ImageComponent> image = std::make_shared<ImageComponent>();
	image->Imageload(iInfo);
	_testBackground.AddComponent(L"Image", image);

	m_pMainCamera->Create({ 0,0,0 }, { (float)g_dwWindowWidth, (float)g_dwWindowHeight });
	return true;
}

bool Sample::Frame()
{
	_testBackground.Frame();
	return true;
}

bool Sample::Render()
{
	_testBackground.Render();
	return true;
}

bool Sample::Release()
{
	_testBackground.Release();
	return true;
}


TGAME("ssda", 1600, 900)
