#pragma once
#include "TWindow.h"
class TDevice : public TWindow
{
public:
    IDXGISwapChain*            m_pSwapChain = nullptr;
    ID3D11Device*              m_pDevice = nullptr;
    IDXGIFactory*              m_pGIFactory = nullptr;
    ID3D11DeviceContext*       m_pImmediateContext = nullptr;
    ID3D11RenderTargetView*    m_pRenderTargetView = nullptr;
    D3D11_VIEWPORT             m_viewPort;
    D3D_DRIVER_TYPE            m_driverType;
    D3D_FEATURE_LEVEL          m_featureLevel;
public:
    HRESULT CreateDevice();
    HRESULT CreateGIFactory();
    HRESULT CreateSwapChain();


public:
   virtual bool Init();
   virtual bool Frame();
   virtual bool PreRender();
   virtual bool PostRender();
   virtual bool Render();
   virtual bool Release();
};

