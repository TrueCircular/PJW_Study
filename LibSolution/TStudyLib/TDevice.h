#pragma once
#include "TWindow.h"
class TDevice : public TWindow
{
public:
    DXGI_SWAP_CHAIN_DESC           m_SwapChainDesc;
    D3D11_VIEWPORT			       m_ViewPort;			// ����Ʈ
public:
    ID3D11Device*                  m_pDevice = nullptr;
    ID3D11DeviceContext*           m_pImmediateContext = nullptr;
    ComPtr<IDXGISwapChain>         m_pSwapChain = nullptr;
    ComPtr<ID3D11RenderTargetView> m_pRenderTargetView = nullptr;
    ComPtr<ID3D11DepthStencilView> m_pDepthStencilView = nullptr;
public:
    bool SetRenderTargetView();
    bool SetDepthStencilView();
    bool SetViewPort();
public:
    bool  Init();
    bool  Frame();
    bool  PreRender();
    bool  PostRender();
    bool  Render();
    bool  Release();
};

