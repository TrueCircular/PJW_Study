#include "Sample.h"
#include "TWriter.h"
#include "ICoreStd.h"
#include "TInput.h"
float g_fMapHalfSizeX = 800;
float g_fMapHalfSizeY = 450;

using std::shared_ptr;

bool Sample::Init()
{
	//Object Init
	_testBackground = make_shared<GameObject>();
	_testObject = make_shared<GameObject>();
	_testSpriteObj = make_shared<GameObject>();
	_testNomalSpriteObj = make_shared<GameObject>();

	_testBackground->SetScale({ g_fMapHalfSizeX ,g_fMapHalfSizeY,1.0 });

	_testObject->SetScale({ 32.f ,32.f ,1.f });

	_testSpriteObj->SetScale({ 50.f,50.f,1.f });
	_testSpriteObj->SetPos({ 100, 0, 0 });

	_testNomalSpriteObj->SetScale({ 50.f, 50.f, 1.f });
	_testNomalSpriteObj->SetPos({ -100.f, 0.f, 0.f });

	//imageComponent DESC
	S_TOBJECT_DESC iInfo;
	iInfo.shaderFileName = L"../../resource/shader/Plane.hlsl";
	iInfo.texFileName = L"../../resource/Map/WorldMap.png";
	//Component Set
	shared_ptr<ImageComponent> image = make_shared<ImageComponent>();
	_testBackground->AddComponent(L"Image", image);
	//_testBackground->AddComponent(L"Image", image); 같은 이름을 가진 컴포넌트를 추가하는것을 허용하지 않음
	image->Imageload(iInfo);

	S_TOBJECT_DESC iInfo2;
	iInfo2.shaderFileName = L"../../resource/shader/Plane.hlsl";
	iInfo2.texFileName = L"../../resource/Sprite/Pet/bird/idle_01.png";

	shared_ptr<ImageComponent> image2 = make_shared<ImageComponent>();
	_testObject->AddComponent(L"Image", image2);
	image2->Imageload(iInfo2);
	image2->VerticalFlip(true);

	TSpriteInfo sInfo;
	ZeroMemory(&sInfo, sizeof(sInfo));
	sInfo.iNumColumn = 5;
	sInfo.iNumRow = 7;
	sInfo.fAnimTimer = 2.0f;
	sInfo.texFile = L"../../resource/Sprite/Characters/archer/1archer_blue.png";
	sInfo.shaderFile = L"../../resource/shader/Plane.hlsl";

	shared_ptr<SpriteComponent> sprite = make_shared<SpriteComponent>();
	_testSpriteObj->AddComponent(L"Sprite", sprite);
	sprite->LoadSpriteImage(E_SpriteType::SPRITE_TYPE_UV, sInfo);

	shared_ptr<AnimationControllerComponent> aCon = make_shared<AnimationControllerComponent>();
	_testSpriteObj->AddComponent(L"AnimController", aCon);
	aCon->AddAnimation(0, 0);
	aCon->AddAnimation(0, 8);
	aCon->AddAnimation(10, 18);
	aCon->SetAnimationState(0);

	T_STR_VECTOR spritevec;
	spritevec.push_back(L"../../resource/Sprite/Characters/Knight/cut/tile000.png");
	spritevec.push_back(L"../../resource/Sprite/Characters/Knight/cut/tile001.png");
	spritevec.push_back(L"../../resource/Sprite/Characters/Knight/cut/tile002.png");
	spritevec.push_back(L"../../resource/Sprite/Characters/Knight/cut/tile003.png");
	spritevec.push_back(L"../../resource/Sprite/Characters/Knight/cut/tile004.png");
	spritevec.push_back(L"../../resource/Sprite/Characters/Knight/cut/tile005.png");
	spritevec.push_back(L"../../resource/Sprite/Characters/Knight/cut/tile006.png");
	spritevec.push_back(L"../../resource/Sprite/Characters/Knight/cut/tile007.png");
	spritevec.push_back(L"../../resource/Sprite/Characters/Knight/cut/tile008.png");
	spritevec.push_back(L"../../resource/Sprite/Characters/Knight/cut/tile009.png");
	spritevec.push_back(L"../../resource/Sprite/Characters/Knight/cut/tile010.png");
	spritevec.push_back(L"../../resource/Sprite/Characters/Knight/cut/tile011.png");
	spritevec.push_back(L"../../resource/Sprite/Characters/Knight/cut/tile012.png");
	spritevec.push_back(L"../../resource/Sprite/Characters/Knight/cut/tile013.png");
	spritevec.push_back(L"../../resource/Sprite/Characters/Knight/cut/tile014.png");

	TSpriteInfo nomalSp;
	nomalSp.Reset();
	nomalSp.fAnimTimer = 1.0f;
	nomalSp.texList = spritevec;
	nomalSp.shaderFile = L"../../resource/shader/Plane.hlsl";

	shared_ptr<SpriteComponent> sprite2 = make_shared<SpriteComponent>();
	_testNomalSpriteObj->AddComponent(L"Sprite", sprite2);
	sprite2->LoadSpriteImage(E_SpriteType::SPRITE_TYPE_NOMAL, nomalSp);

	shared_ptr<AnimationControllerComponent> aCon2 = make_shared<AnimationControllerComponent>();
	_testNomalSpriteObj->AddComponent(L"AnimController", aCon2);
	aCon2->AddAnimation(0, 0);
	aCon2->AddAnimation(0, 14);
	aCon2->SetAnimationState(1);
	//Create Camera
	m_pMainCamera->Create({ 0,0,0 }, { (float)g_dwWindowWidth, (float)g_dwWindowHeight });
	return true;
}

bool Sample::Frame()
{
	//if (I_Input.GetInstance().m_dwKeyState['A'] >= KEY_PUSH &&
	//	I_Input.GetInstance().m_dwKeyState['D'] < KEY_PUSH)
	//{
	//	_testSpriteObj->m_vPos.x -= 100 * g_fSecondPerFrame;
	//}
	//if (I_Input.GetInstance().m_dwKeyState['D'] >= KEY_PUSH &&
	//	I_Input.GetInstance().m_dwKeyState['A'] < KEY_PUSH)
	//{
	//	_testSpriteObj->m_vPos.x += 100 * g_fSecondPerFrame;
	//}
	//if (I_Input.GetInstance().m_dwKeyState['W'] >= KEY_PUSH &&
	//	I_Input.GetInstance().m_dwKeyState['S'] < KEY_PUSH)
	//{
	//	_testSpriteObj->m_vPos.y += 100 * g_fSecondPerFrame;
	//}
	//if (I_Input.GetInstance().m_dwKeyState['S'] >= KEY_PUSH &&
	//	I_Input.GetInstance().m_dwKeyState['W'] < KEY_PUSH)
	//{
	//	_testSpriteObj->m_vPos.y -= 100 * g_fSecondPerFrame;
	//}

	TVector3 mouse = I_Input.GetWorldPos({ (float)g_dwWindowWidth, (float)g_dwWindowHeight }, m_pMainCamera->m_vCameraPos);
	TVector2 mouse2 = I_Input.GetWorldPosVec2({ (float)g_dwWindowWidth, (float)g_dwWindowHeight }, m_pMainCamera->m_vCameraPos);

	if (m_pMainCamera->m_rt.ToPoint(mouse2))
	{
		_isCamMove = false;
	}
	else
	{
		_isCamMove = true;
	}
	
	if (_isCamMove)
	{
		TVector3 mDir = mouse - m_pMainCamera->m_vCameraPos;
		mDir.Normalize();
		TVector3 velo = mDir * 400.f * g_fSecondPerFrame;
		m_pMainCamera->m_vCameraPos += velo;
	}

	_testBackground->Frame();
	_testObject->Frame();
	_testSpriteObj->Frame();
	_testNomalSpriteObj->Frame();


	if (I_Input.GetInstance().m_dwKeyState[VK_NUMPAD1] == KEY_PUSH)
	{
		m_pMainCamera->m_zoomState = E_CameraZoomState::CAMERA_ZOOM_ONCE;
	}
	if (I_Input.GetInstance().m_dwKeyState[VK_NUMPAD2] == KEY_PUSH)
	{
		m_pMainCamera->m_zoomState = E_CameraZoomState::CAMERA_ZOOM_TWICE;
	}
	if (I_Input.GetInstance().m_dwKeyState[VK_NUMPAD3] == KEY_PUSH)
	{
		m_pMainCamera->m_zoomState = E_CameraZoomState::CAMERA_ZOOM_TRIPLE;
	}


	return true;
}

bool Sample::Render()
{

	_testBackground->Render();
	_testObject->Render();
	_testSpriteObj->Render();
	_testNomalSpriteObj->Render();
	return true;
}

bool Sample::Release()
{
	_testBackground->Release();
	_testObject->Release();
	_testSpriteObj->Release();
	_testNomalSpriteObj->Release();

	return true;
}


TGAME("ssda", 1600, 900)
