#include "TCore.h"
#include "ICoreStd.h"

void  TCore::CreateBlendState()
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
void TCore::CreateSamplerState()
{
    D3D11_SAMPLER_DESC samDesc;
    ZeroMemory(&samDesc, sizeof(samDesc));

    samDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    samDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    samDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    samDesc.MipLODBias = 0;
    samDesc.MaxAnisotropy = 16;

    samDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    samDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;

    samDesc.BorderColor[0] = 1.0f;
    samDesc.BorderColor[1] = 0.0f;
    samDesc.BorderColor[2] = 0.0f;
    samDesc.BorderColor[3] = 1.0f;
    samDesc.MinLOD = 0;
    samDesc.MaxLOD = D3D11_FLOAT32_MAX;

    HRESULT hr = m_pDevice->CreateSamplerState(&samDesc, &m_SamplerState);
}
void TCore::CreateDepthStencilState()
{
    HRESULT hr;
    // 깊이버퍼 상태값 세팅
    D3D11_DEPTH_STENCIL_DESC dsDescDepth;
    ZeroMemory(&dsDescDepth, sizeof(D3D11_DEPTH_STENCIL_DESC));
    dsDescDepth.DepthEnable = TRUE;
    dsDescDepth.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    // 해당 픽셀의 깊이 연산을 하여 출력여부를 판단한다.
    // 지형의 깊이 값 >=  깊이버퍼의 픽셀값(1.0f) 
    dsDescDepth.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
    //Stencil
    dsDescDepth.StencilEnable = FALSE;
    dsDescDepth.StencilReadMask = 1;
    dsDescDepth.StencilWriteMask = 1;
    dsDescDepth.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
    dsDescDepth.FrontFace.StencilPassOp = D3D11_STENCIL_OP_INCR;
    dsDescDepth.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
    dsDescDepth.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
    // 디폴트 값
    dsDescDepth.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
    dsDescDepth.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
    dsDescDepth.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
    dsDescDepth.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;

    if (FAILED(hr = m_pDevice->CreateDepthStencilState(&dsDescDepth,
        m_pDepthStencilState.GetAddressOf())))
    {
        return;
    }
    dsDescDepth.DepthEnable = FALSE;
    if (FAILED(hr = m_pDevice->CreateDepthStencilState(&dsDescDepth,
        m_pDepthStencilStateDisable.GetAddressOf())))
    {
        return;
    }
}
void TCore::CreateRasterizerState()
{
    HRESULT hr;
    D3D11_RASTERIZER_DESC rd;
    ZeroMemory(&rd, sizeof(rd));
    rd.FillMode = D3D11_FILL_SOLID;
    rd.CullMode = D3D11_CULL_NONE;

    hr = m_pDevice->CreateRasterizerState(&rd, m_pRSSolid.GetAddressOf());

    rd.FillMode = D3D11_FILL_WIREFRAME;
    hr = m_pDevice->CreateRasterizerState(&rd, m_pRSWireFrame.GetAddressOf());

}
void TCore::ResizeDevice(UINT width, UINT height)
{
    HRESULT hr;
    if (m_pDevice == nullptr) return;

    DeleteDxResource();

    // rendertarget    
    m_pImmediateContext->OMSetRenderTargets(0, nullptr, nullptr);
    m_pRenderTargetView->Release();
    m_pDepthStencilView->Release();

    hr = m_pSwapChain->ResizeBuffers(m_SwapChainDesc.BufferCount,
        width, height, m_SwapChainDesc.BufferDesc.Format, m_SwapChainDesc.Flags);

    m_pSwapChain->GetDesc(&m_SwapChainDesc);

    SetRenderTargetView();
    SetDepthStencilView();
    SetViewPort();

    GetClientRect(g_hWnd, &m_rcClient);
    g_dwWindowWidth = m_dwWindowWidth = m_rcClient.right;
    g_dwWindowHeight = m_dwWindowHeight = m_rcClient.bottom;

    CreateDxResource();
}
bool TCore::DeleteDxResource()
{
    I_Writer.DeleteDxResource();
    return true;
}
bool TCore::CreateDxResource()
{
    if (m_pSwapChain)
    {
        IDXGISurface1* pBackBuffer;
        HRESULT hr = m_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface1),
            (LPVOID*)&pBackBuffer);
        if (SUCCEEDED(hr))
        {
            I_Writer.CreateDxResource(pBackBuffer);
        }
        if (pBackBuffer) pBackBuffer->Release();
    }
    return true;
}
bool  TCore::Init() { return true; }
bool  TCore::Frame() { return true; }
bool  TCore::Render() { return true; }
bool  TCore::Release() { return true; }
bool  TCore::EngineInit()
{
    TDevice::Init();

    ICore::g_pDevice = m_pDevice;
    ICore::g_pContext = m_pImmediateContext;

    CreateBlendState();
    CreateSamplerState();
    CreateDepthStencilState();
    CreateRasterizerState();

    I_Tex.Set(m_pDevice, m_pImmediateContext);
    I_Shader.Set(m_pDevice, m_pImmediateContext);

    m_GameTimer.Init();    
    TInput::GetInstance().Init();  

    m_pMainCamera = std::make_shared<TCamera>();
    m_pMainCamera->Init();
    ICore::g_pMainCamera = m_pMainCamera.get();

    I_Writer.Init();    
    if (m_pSwapChain)
    {
        IDXGISurface1* pBackBuffer;
        HRESULT hr = m_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface1),
            (LPVOID*)&pBackBuffer);
        if (SUCCEEDED(hr))
        {
            I_Writer.Create(pBackBuffer);
        }
        if (pBackBuffer) pBackBuffer->Release();
    }

	Init();    
	return true;
}
bool  TCore::EngineFrame()
{
    m_GameTimer.Frame();
    TInput::GetInstance().Frame();
    ICore::g_pMainCamera->Frame();
    TDevice::Frame();
    I_Writer.Frame();
	Frame();
	return true;
}
bool  TCore::EngineRender()
{
    TDevice::PreRender();
    m_pImmediateContext->OMSetBlendState(m_AlphaBlend.Get(), 0, -1);
    m_pImmediateContext->PSSetSamplers(0, 1, m_SamplerState.GetAddressOf());
    m_pImmediateContext->OMSetDepthStencilState(m_pDepthStencilState.Get(), 1);
    m_pImmediateContext->RSSetState(m_pRSSolid.Get());
    // debug V
    if (I_Input.Getkey('V') == KEY_HOLD)
    {
        m_pImmediateContext->RSSetState(m_pRSWireFrame.Get());
    }

	Render();

    ICore::g_pMainCamera->Frame();
    m_GameTimer.Render();
    TInput::GetInstance().Render();

    I_Writer.Render();
    TDevice::PostRender();

	return true;
}
bool  TCore::EngineRelease()
{
	Release();

    TInput::GetInstance().Release();
    ICore::g_pMainCamera->Release();
    //I_Shader.Release();
    //I_Tex.Release();
    I_Writer.Release();
    TDevice::Release();
	return true;
}
bool TCore::Run()
{
    EngineInit();
    MSG msg = { 0 };
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            // 게임로직을 처리
            if (!EngineFrame() || !EngineRender())
            {
                break;
            }
        }
    }
    EngineRelease();
    return true;
}