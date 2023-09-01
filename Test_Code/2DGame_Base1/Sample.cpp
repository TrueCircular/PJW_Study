#include "Sample.h"
#include "TWriter.h"

float g_fMapHalfSizeX = 800;
float g_fMapHalfSizeY = 450;

bool Sample::Init()
{
	srand(time(NULL));

	main = new TPlaneObj;
	main->Set(m_pDevice, m_pImmediateContext);
	main->SetPos({ 0,0,0, });
	main->SetScale({ g_fMapHalfSizeX, g_fMapHalfSizeY, 1.0f });
	main->Create(L"../../resource/Background/Main.png", L"../../resource/shader/Plane.hlsl");

	m_pMainCamera->Create({ 0,0,0 }, { (float)g_dwWindowWidth, (float)g_dwWindowHeight });

	music = I_Sound.Load(L"../../resource/Sound/Scene/Main.wav");
	music->Play(true);
	music->Volume(0.35f);
	
	T_STR_VECTOR birdVec;
	birdVec.push_back(L"../../resource/Sprite/Pet/bird/move_01.png");
	birdVec.push_back(L"../../resource/Sprite/Pet/bird/move_02.png");
	birdVec.push_back(L"../../resource/Sprite/Pet/bird/move_03.png");
	birdVec.push_back(L"../../resource/Sprite/Pet/bird/move_04.png");
	birdVec.push_back(L"../../resource/Sprite/Pet/bird/move_05.png");
	birdVec.push_back(L"../../resource/Sprite/Pet/bird/move_06.png");
	birdVec.push_back(L"../../resource/Sprite/Pet/bird/move_07.png");
	birdVec.push_back(L"../../resource/Sprite/Pet/bird/move_08.png");

	TSpriteInfo info;
	info.Reset();
	info.p = { -700.f,360.f,0.f };
	info.s = { 30.f,30.f,1.0f };
	info.iNumRow = 16;
	info.iNumColumn = 16;
	info.fAnimTimer = 1.f;
	info.texFile = L"../../resource/Sprite/Pet/bird/move_01.png";
	info.texList = birdVec;
	info.shaderFile = L"../../resource/shader/Plane.hlsl";

	for (int i = 1; i <= 8; i++)
	{
		SPRITE_OBJ temp = std::make_shared<TSpriteTexture>();

		if (i % 3 == 0 ||
			i % 5 == 0)
		{
			info.p.y = 360.f + randstep(0, 50.f);
		}
		else if (i % 2 == 0)
		{
			info.p.y = 360.f + randstep(-50, 0);
		}
		else
		{
			info.p.y = 360.f;
		}
		info.p.x += 50.f;
		temp->m_isFlip = true;
		temp->Load(m_pDevice, m_pImmediateContext, info);
		bird.push_back(temp);
	}

	return true;
}

bool Sample::Frame()
{
	if (_isBack == false)
	{
		gradation += 0.45f * g_fSecondPerFrame;

		if (gradation > 1.0f)
			_isBack = true;
	}
	else
	{
		gradation -= 0.45f * g_fSecondPerFrame;

		if (gradation < 0.f)
			_isBack = false;
	}

	I_Sound.Frame();
	main->Frame();

	for (int i = 0; i < bird.size(); i++)
	{
		bird[i]->m_vPos.x += randstep(100, 600.f) * g_fSecondPerFrame;

		if (bird[i]->m_vPos.x >= g_fMapHalfSizeX)
			bird[i]->m_vPos.x = -g_fMapHalfSizeX;

		bird[i]->Frame();
	}

	return true;
}

bool Sample::Render()
{
	main->SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matOrthoProjection);
	main->Render();


	for (int i = 0; i < bird.size(); i++)
	{
		bird[i]->SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matOrthoProjection);
		bird[i]->Render();
	}

	std::wstring temp = L"New World";
	I_Writer.AddText(temp, 330, 225 - 180, { 1,1,0.5f,gradation });

	std::wstring temp2 = L"-New Game-";
	I_Writer.AddText(temp2, 315, 225 + 215, { 0.124f,0.206f,0.118f,0.75f });

	std::wstring temp3 = L"-Continue-";
	I_Writer.AddText(temp3, 320, 225 + 255, { 0.124f,0.206f,0.118f,0.75f });

	std::wstring temp4 = L"-Exit-";
	I_Writer.AddText(temp4, 355, 225 + 295, { 0.124f,0.206f,0.118f,0.75f });
	return true;
}

bool Sample::Release()
{
	return true;
}


TGAME("ssda", 1600, 900)
