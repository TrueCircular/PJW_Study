#include "TDevice.h"

HRESULT TDevice::CreateDevice()
{
	HRESULT totalHR;
	UINT cDeviceFlag = 0;
#ifdef _DEBUG
	cDeviceFlag |= D3D11_CREATE_DEVICE_DEBUG;
#endif // _DEBUG

	D3D_DRIVER_TYPE driverType[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE
	};
	UINT numDriverType = sizeof(driverType) / sizeof(driverType[0]);

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0
	};
	UINT numFeatureLevels = sizeof(featureLevels) / sizeof(featureLevels[0]);

	D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;

	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverType; driverTypeIndex++)
	{
		m_driverType = driverType[driverTypeIndex];
		if (FAILED(totalHR = D3D11CreateDevice(NULL, m_driverType, NULL, cDeviceFlag,
			featureLevels, numFeatureLevels, D3D11_SDK_VERSION, &m_pDevice, &featureLevel, &m_pImmediateContext)))
		{
			continue;
		}
		break;
	}

	if (FAILED(totalHR))
	{
		return totalHR;
	}

	return totalHR;
}

HRESULT TDevice::CreateGIFactory()
{
	HRESULT totalHR;

	if (FAILED(totalHR = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&m_pGIFactory)))
	{
		return S_FALSE;
	}

	return totalHR;
}

HRESULT TDevice::CreateSwapChain()
{
	if (m_pGIFactory == NULL) return S_FALSE;
	HRESULT totalHR;

	DXGI_SWAP_CHAIN_DESC sDesc;
	ZeroMemory(&sDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
	sDesc.BufferDesc.Width = m_dwWindowWidth;
	sDesc.BufferDesc.Height = m_dwWindowHeight;
	sDesc.BufferDesc.RefreshRate.Numerator = 60;
	sDesc.BufferDesc.RefreshRate.Denominator = 1;
	sDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sDesc.SampleDesc.Count = 1;
	sDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sDesc.BufferCount = 1;
	sDesc.OutputWindow = m_hWnd;
	sDesc.Windowed = true;

	if (FAILED(totalHR = m_pGIFactory->CreateSwapChain(m_pDevice, &sDesc, &m_pSwapChain)))
	{
		return totalHR;
	}

	ID3D11Texture2D* pBackBuffer;
	totalHR = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	if (SUCCEEDED(totalHR))
	{
		totalHR = m_pDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_pRenderTargetView);
		if (FAILED(totalHR))
		{
			pBackBuffer->Release();
			return totalHR;
		}
		m_pImmediateContext->OMSetRenderTargets(1, &m_pRenderTargetView, NULL);
	}
	pBackBuffer->Release();

	ZeroMemory(&m_viewPort, sizeof(D3D11_VIEWPORT));
	m_viewPort.Width = m_dwWindowWidth;
	m_viewPort.Height = m_dwWindowHeight;
	m_viewPort.MaxDepth = 1.0f;
	m_pImmediateContext->RSSetViewports(1, &m_viewPort);

	return totalHR;
}

bool TDevice::Init()
{
	CreateDevice();
	CreateGIFactory();
	CreateSwapChain();
	return true;
}

bool TDevice::Frame()
{
	return true;
}

bool TDevice::PreRender()
{
	if (m_pImmediateContext == NULL) return false;

	float color[4] = { 1.f, 1.f, 1.f, 1 };
	m_pImmediateContext->ClearRenderTargetView(m_pRenderTargetView, color);

	return true;
}

bool TDevice::PostRender()
{
	if (m_pSwapChain == NULL) return false;

	HRESULT hr = m_pSwapChain->Present(0, 0);

	if (FAILED(hr))
	{
		return false;
	}
	return true;
}

bool TDevice::Render()
{
	PreRender();
	PostRender();
	return true;
}

bool TDevice::Release()
{
	if (m_pGIFactory) m_pGIFactory->Release();
	if (m_pDevice) m_pDevice->Release();
	if (m_pImmediateContext) m_pImmediateContext->ClearState();
	if (m_pRenderTargetView) m_pRenderTargetView->Release();
	if (m_pSwapChain) m_pSwapChain->Release();
	if (m_pImmediateContext) m_pImmediateContext->Release();

	m_pDevice = NULL;
	m_pSwapChain = NULL;
	m_pRenderTargetView = NULL;
	m_pImmediateContext = NULL;
	m_pGIFactory = NULL;
	return true;
}
