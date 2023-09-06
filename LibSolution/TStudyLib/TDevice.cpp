#include "TDevice.h"

bool TDevice::DisableBackfaceCulling(D3D11_FILL_MODE _fillMode)
{
    if (m_rsState != nullptr) m_rsState->Release();

    D3D11_RASTERIZER_DESC rDesc;
    ZeroMemory(&rDesc, sizeof(rDesc));
    rDesc.FillMode = _fillMode;
    rDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
    HRESULT hr = m_pDevice->CreateRasterizerState(&rDesc, &m_rsState);

    if (SUCCEEDED(hr))
    {
        m_pImmediateContext->RSSetState(m_rsState);
        return true;
    }

    return false;
}

bool  TDevice::Init()
{
    DXGI_SWAP_CHAIN_DESC SwapChainDesc;
    ZeroMemory(&SwapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
    SwapChainDesc.BufferDesc.Width = g_dwWindowWidth;
    SwapChainDesc.BufferDesc.Height = g_dwWindowHeight;
    SwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
    SwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
    SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    SwapChainDesc.SampleDesc.Count = 1;
    SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    SwapChainDesc.BufferCount = 1;
    SwapChainDesc.OutputWindow = m_hWnd;
    SwapChainDesc.Windowed = true;
    SwapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG::DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    D3D_DRIVER_TYPE DriverType = D3D_DRIVER_TYPE_HARDWARE;
    UINT Flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#ifdef _DEBUG
    Flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
    D3D_FEATURE_LEVEL pFeatureLevels = D3D_FEATURE_LEVEL_11_0;

    // 1) 디바이스
    HRESULT hr = D3D11CreateDeviceAndSwapChain(
        NULL,
        DriverType,
        NULL,
        Flags,
        &pFeatureLevels, 1,
        D3D11_SDK_VERSION,
        &SwapChainDesc,

        &m_pSwapChain,   // 백버퍼인터페이스
        &m_pDevice,      // dx 인터페이스( 생성 )
        NULL,
        &m_pImmediateContext); // dx 인터페이스( 관리 )
    if (FAILED(hr))
    {
        return false;
    }
    // 2) 백버퍼 얻어서
    ID3D11Texture2D* pBackBuffer;
    hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
    if (SUCCEEDED(hr))
    {
        // 3) 렌더타켓 지정하고
        hr = m_pDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_pRenderTargetView);
        if (FAILED(hr))
        {
            pBackBuffer->Release();
            return false;
        }
        m_pImmediateContext->OMSetRenderTargets(1, &m_pRenderTargetView, NULL);
    }
    pBackBuffer->Release();


    m_ViewPort.Width = SwapChainDesc.BufferDesc.Width;
    m_ViewPort.Height = SwapChainDesc.BufferDesc.Height;
    m_ViewPort.MinDepth = 0.0f;
    m_ViewPort.MaxDepth = 1.0f;
    m_ViewPort.TopLeftX = 0;
    m_ViewPort.TopLeftY = 0;
    m_pImmediateContext->RSSetViewports(1, &m_ViewPort);

    m_rsFillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
    DisableBackfaceCulling(m_rsFillMode);


    return true;
}
bool  TDevice::Frame()
{

    return true;
}
bool  TDevice::PreRender()
{   
    float color[4] = { 0.343f,0.34522f,0.64333f,1 };
    m_pImmediateContext->ClearRenderTargetView(m_pRenderTargetView, color);   
    return true;
}
bool  TDevice::PostRender()
{
    DisableBackfaceCulling(m_rsFillMode);

    HRESULT hr = m_pSwapChain->Present(0, 0);
    if (FAILED(hr))
    {
        return false;
    }
    return true;
}
bool  TDevice::Render()
{
    PreRender();
    PostRender();
    return true;
}
bool  TDevice::Release()
{
    if (m_pSwapChain)m_pSwapChain->Release();
    if (m_pDevice)m_pDevice->Release();
    if (m_pImmediateContext)m_pImmediateContext->Release();
    return true;
}
