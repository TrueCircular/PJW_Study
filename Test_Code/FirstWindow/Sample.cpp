#include <Windows.h>
#include "Sample.h"


int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
    Sample mySample;
    mySample.SetRegisterClassWindow(hInstance);
    mySample.SetWindow(L"³ª´Ù", 800, 600);
    mySample.Run();

    return 0;
}

bool Sample::Init()
{
    DXGI_SWAP_CHAIN_DESC sDesc;
    ZeroMemory(&sDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
    sDesc.BufferDesc.Width = 800;
    sDesc.BufferDesc.Height = 600;
    sDesc.BufferDesc.RefreshRate.Numerator = 60;
    sDesc.BufferDesc.RefreshRate.Denominator = 1;
    sDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sDesc.SampleDesc.Count = 1;
    sDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sDesc.BufferCount = 1;
    sDesc.OutputWindow = m_hWnd;
    sDesc.Windowed = true;

    D3D_DRIVER_TYPE driverType = D3D_DRIVER_TYPE_HARDWARE;
    UINT flags = 0;
    D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;
    HRESULT hr = D3D11CreateDeviceAndSwapChain(
        NULL,
        driverType,
        NULL,
        flags,
        &featureLevel,
        1,
        D3D11_SDK_VERSION,
        &sDesc,
        &m_pSwapChain,
        &m_pDevice,
        NULL,
        &m_pImmediateContext
    );
    if (FAILED(hr))
    {
        return false;
    }
    ID3D11Texture2D* pBackBuffer;
    hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
    if (SUCCEEDED(hr))
    {
        hr = m_pDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_pRenderTargetView);
        if (FAILED(hr))
        {
            pBackBuffer->Release();
            return false;
       }
        m_pImmediateContext->OMSetRenderTargets(1, &m_pRenderTargetView, NULL);
    }
    pBackBuffer->Release();
   
    return true;
}

bool Sample::Frame()
{
    return true;
}

bool Sample::Render()
{ 
    float color[4] = { 0.219f, 0.156f, 0.255f, 1 };
    m_pImmediateContext->ClearRenderTargetView(m_pRenderTargetView, color);
    HRESULT hr = m_pSwapChain->Present(0, 0);
    if (FAILED(hr))
    {
        return false;
    }

    return true;
}

bool Sample::Release()
{
    if (m_pSwapChain) m_pSwapChain->Release();
    if (m_pDevice) m_pDevice->Release();
    if (m_pImmediateContext) m_pImmediateContext->Release();

    return true;
}
