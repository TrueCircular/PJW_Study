#include "Sample.h"
#include "TWriter.h"
#include "ICoreStd.h"

float g_fMapHalfSizeX = 800;
float g_fMapHalfSizeY = 450;

using std::shared_ptr;

bool Sample::Init()
{
	//Object Init
	_testBackground = make_shared<GameObject>();
	_testObject = make_shared<GameObject>();
	_testSpriteObj = make_shared<GameObject>();

	//imageComponent DESC
	S_TOBJECT_DESC iInfo;
	iInfo.pos = { 0,0,0 };
	iInfo.scale = { g_fMapHalfSizeX ,g_fMapHalfSizeY ,1.0 };
	iInfo.shaderFileName = L"../../resource/shader/Plane.hlsl";
	iInfo.texFileName = L"../../resource/Background/Main.png";
	//Component Set
	shared_ptr<ImageComponent> image = make_shared<ImageComponent>();
	_testBackground->AddComponent(L"Image", image);
	//_testBackground->AddComponent(L"Image", image); 같은 이름을 가진 컴포넌트를 추가하는것을 허용하지 않음
	image->Imageload(iInfo);

	S_TOBJECT_DESC iInfo2;
	iInfo2.pos = { 0,0,0 };
	iInfo2.scale = { 32 ,32 ,1.0 };
	iInfo2.shaderFileName = L"../../resource/shader/Plane.hlsl";
	iInfo2.texFileName = L"../../resource/Sprite/Pet/bird/idle_01.png";

	shared_ptr<ImageComponent> image2 = make_shared<ImageComponent>();
	_testObject->AddComponent(L"Image", image2);
	image2->Imageload(iInfo2);
	image2->VerticalFlip(false);

	TSpriteInfo sInfo;
	ZeroMemory(&sInfo, sizeof(sInfo));
	sInfo.iNumColumn = 5;
	sInfo.iNumRow = 7;
	sInfo.s = { 100,100,1 };
	sInfo.fAnimTimer = 3.0f;
	sInfo.texFile = L"../../resource/Sprite/Characters/archer/1archer_blue.png";
	sInfo.shaderFile = L"../../resource/shader/Plane.hlsl";

	shared_ptr<SpriteComponent> sprite = make_shared<SpriteComponent>();
	_testSpriteObj->AddComponent(L"sprite", sprite);
	sprite->SetSpriteType(E_SpriteType::SPRITE_TYPE_UV);
	sprite->LoadSpriteImage(sInfo);

	_testSpriteObj->m_vPos.x += 100;
	//Create Camera
	m_pMainCamera->Create({ 0,0,0 }, { (float)g_dwWindowWidth, (float)g_dwWindowHeight });
	return true;
}

bool Sample::Frame()
{
	_testBackground->Frame();
	_testObject->Frame();
	_testSpriteObj->Frame();
	return true;
}

bool Sample::Render()
{
	_testBackground->Render();
	_testObject->Render();
	_testSpriteObj->Render();
	return true;
}

bool Sample::Release()
{
	_testBackground->Release();
	_testObject->Release();
	return true;
}


TGAME("ssda", 1600, 900)
