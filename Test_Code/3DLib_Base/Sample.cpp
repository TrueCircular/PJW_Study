#include "Sample.h"
int Sample::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	m_ShaderEditer.MsgProc(hWnd, message, wParam, lParam);
	return -1;
}
bool Sample::Init()
{
	m_ShaderEditer.Create(L"CustomizeMap.hlsl", m_hWnd);

	if (FAILED(m_LineDraw.Create(GetDevice(), Res(L"shader/line.hlsl").c_str())))
	{
		MessageBox(0, _T("m_LineDraw 실패"), _T("Fatal error"), MB_OK);
		return 0;
	}

	TMapDesc MapDesc = { 50, 50, 1.0f, 0.1f, Res(L"map/castle.jpg"), L"CustomizeMap.hlsl" };
	m_CustomMap.Init(GetDevice(), m_pImmediateContext);
	if (FAILED(m_CustomMap.Load(MapDesc)))
	{
		return false;
	}
	D3D11_SHADER_RESOURCE_VIEW_DESC VD;
	m_CustomMap.m_dxobj.g_pTextureSRV.Get()->GetDesc(&VD);

	if (FAILED(CreateResource()))
	{
		return false;
	}
	//--------------------------------------------------------------------------------------
	// 카메라  행렬 
	//--------------------------------------------------------------------------------------
	SAFE_NEW(m_pMainCamera, TCamera);
	m_pMainCamera->SetViewMatrix(TVector3(0.0f, 30.0f, 0.0f),
		TVector3(0.0f, 0.0f, 1.0f));
	m_pMainCamera->SetProjMatrix(XM_PI * 0.25f,
		m_SwapChainDesc.BufferDesc.Width / (float)(m_SwapChainDesc.BufferDesc.Height),
		1.0f, 1000.0f);
	m_pMainCamera->m_fSpeed = 30.f;
	return true;
}
bool Sample::Render()
{
	DX::ApplyDSS(m_pImmediateContext, DX::TDxState::g_pDSSDepthEnable);
	DX::ApplyBS(m_pImmediateContext, DX::TDxState::g_pAlphaBlend);
	m_CustomMap.SetMatrix(m_pMainCamera->GetWorldMatrix(), m_pMainCamera->GetViewMatrix(), m_pMainCamera->GetProjMatrix());
	return m_CustomMap.Render(m_pImmediateContext);
}
bool Sample::Release()
{
	m_ShaderEditer.Release();
	return m_CustomMap.Release();
}
bool Sample::Frame()
{
	if (!m_ShaderEditer.Frame()) return false;
	if (m_ShaderEditer.IsReload())
	{
		m_CustomMap.ResetShader();
		if (FAILED(m_CustomMap.LoadShaderFile(m_pd3dDevice, L"CustomizeMap.hlsl")))
		{
			MessageBox(0, _T("LoadShaderFile 실패"), _T("Fatal error"), MB_OK);
			return 0;
		}
	}

	//// 2초당 1회전( 1 초 * XM_PI = 3.14 )
	//float t = cosf(m_Timer.GetElapsedTime())*0.5f;// *XM_PI;
	//for (int z = 0; z < m_CustomMap.m_iNumRows; z++)
	//{
	//	for (int x = 0; x < m_CustomMap.m_iNumCols; x++)
	//	{
	//		int iIndex = z*m_CustomMap.m_iNumCols + x;
	//		float fCos = cosf(t*x);
	//		float fSin = sinf(t*z);
	//		m_CustomMap.m_VertexList[iIndex].p.y =	fCos + fSin;
	//	}
	//}
	//g_pImmediateContext->UpdateSubresource(
	//	m_CustomMap.m_dxobj.g_pVertexBuffer.Get(),0, 0, &m_CustomMap.m_VertexList.at(0), 0, 0);

	m_pMainCamera->Frame();
	return m_CustomMap.Frame();
}
bool Sample::DrawDebug()
{
	DX::ApplyDSS(m_pImmediateContext, DX::TDxState::g_pDSSDepthDisable);
	m_LineDraw.SetMatrix(NULL, m_pMainCamera->GetViewMatrix(), m_pMainCamera->GetProjMatrix());
	TVector3 vStart(0, 0, 0);
	TVector3 vEnd(1000, 0, 0);
	m_LineDraw.Draw(m_pImmediateContext, vStart, vEnd, TVector4(1, 0, 0, 1.0f));
	vEnd = TVector3(0, 1000, 0);
	m_LineDraw.Draw(m_pImmediateContext, vStart, vEnd, TVector4(0, 1, 0, 1.0f));
	vEnd = TVector3(0, 0, 1000);
	m_LineDraw.Draw(m_pImmediateContext, vStart, vEnd, TVector4(0, 0, 1, 1.0f));
	if (!TBasisLib::DrawDebug()) return false;
	return true;
}
//--------------------------------------------------------------------------------------
// 
//--------------------------------------------------------------------------------------
HRESULT Sample::CreateResource()
{
	HRESULT hr = S_OK;
	if (m_pMainCamera)
	{
		float fAspectRatio = m_SwapChainDesc.BufferDesc.Width /
			(float)m_SwapChainDesc.BufferDesc.Height;
		m_pMainCamera->SetProjMatrix(XM_PI / 4, fAspectRatio, 0.1f, 500.0f);
	}
	return hr;
}
//--------------------------------------------------------------------------------------
// 
//--------------------------------------------------------------------------------------
HRESULT Sample::DeleteResource()
{
	HRESULT hr = S_OK;
	if (m_pImmediateContext) m_pImmediateContext->ClearState();
	return S_OK;
}

Sample::Sample(void)
{
	m_pMainCamera = nullptr;
}

Sample::~Sample(void)
{
}
TBASIS_RUN(L"TBasisSample CustomizeMap");

