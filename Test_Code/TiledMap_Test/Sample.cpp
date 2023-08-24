#include "Sample.h"

float g_fMapHalfSizeX = 400;
float g_fMapHalfSizeY = 300;

bool Sample::Init()
{
	m_pMapObj = new TPlaneObj;
	m_pMapObj->Set(m_pDevice, m_pImmediateContext);
	m_pMapObj->SetPos({ 0.0f,0.0f ,0.0f });
	m_pMapObj->SetScale(TVector3(g_fMapHalfSizeX, g_fMapHalfSizeY, 1.0f));
	m_pMapObj->Create(L"../../resource/topdownmap.jpg", L"../../resource/shader/Plane.hlsl");
	
	CreateBlendState();

	_effect = new EffectObj;
	_effect->AddSpriteAddress(L"../../resource/Sprite/Fire/", 23);
	_effect->Init(m_pDevice, m_pImmediateContext,TVector3(0.f,0.f,0.f),TVector3(100.f,100.f,1.f));
	_effect->PlayEffect(true);
	m_MainCamera.Create({ 0.0f,0.0f, 0.0f }, { (float)m_dwWindowWidth, (float)m_dwWindowHeight });
	return true;
}
bool Sample::Frame()
{
	angle += DegreeToRadian(1);
	
	move.x += -sinf(angle);
	move.y += cosf(angle);

	_effect->SetPos(move);
	_effect->Frame();
	return true;
}
bool Sample::Render()
{
	m_pImmediateContext->OMSetBlendState(m_AlphaBlend, 0, -1);
	m_pMapObj->SetMatrix(nullptr, &m_MainCamera.m_matView, &m_MainCamera.m_matOrthoProjection);
	m_pMapObj->Render();

	_effect->SetMatrix(nullptr, &m_MainCamera.m_matView, &m_MainCamera.m_matOrthoProjection);
	_effect->Render();
	return true;
}
bool Sample::Release()
{
	m_pMapObj->Release();
	delete m_pMapObj;
	_effect->Release();
	delete _effect;
	return true;
}
void Sample::CreateBlendState()
{
	// alpha blending
	D3D11_BLEND_DESC bsd;
	ZeroMemory(&bsd, sizeof(bsd));
	bsd.RenderTarget[0].BlendEnable = true;
	bsd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	bsd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	bsd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	// 알파블랜딩 공식 - 소스(float4(0,1,0,0.5f)), 대상(1,0,0,1)
	//finalcolor(RGB) = SrcColor* SrcBlend   + DestColor*DestBlend
	//           = Scrcolor* alphaValue + DestColor * (1.0f-alphaValue)
	//           = 0,1,0 * 0.5f + 1,0,0 * (1.0f-0.5f)
	// //        만약 t= 0.0f; 결과 => 배경만 나온다.
	// //        만약 t= 1.0f; 결과 => 소스만 나온다.
	//           만약 t= 0.5f; 결과 - >소스컬러*0.5 + 배경컬러*0.5f
	//           = 0,1,0 * t + 1,0,0 * (1.0f-t)
	//           =  r*t,b*t,b*t + r*(1.0f-t),b*(1.0f-t),b*(1.0f-t)

	// (A)
	bsd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	bsd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bsd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;

	bsd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	m_pDevice->CreateBlendState(&bsd, &m_AlphaBlend);
}

TGAME("KGCA", 800, 600);