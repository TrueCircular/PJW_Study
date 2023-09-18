#pragma once
#include "TWindow.h"
class TDevice : public TWindow
{
public:
    IDXGISwapChain* m_pSwapChain = nullptr;
    ID3D11Device* m_pDevice = nullptr;
    ID3D11DeviceContext* m_pImmediateContext = nullptr;
    ID3D11RenderTargetView* m_pRenderTargetView = nullptr;
    ID3D11RasterizerState*  m_rsState = nullptr;
    ComPtr<ID3D11DepthStencilView> m_pDepthStencilView = nullptr;

    D3D11_VIEWPORT			m_ViewPort;			// ºäÆ÷Æ®
    D3D11_FILL_MODE         m_rsFillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;

public:
    bool  DisableBackfaceCulling(D3D11_FILL_MODE _fillMode);
public:
    bool  Init();
    bool  Frame();
    bool  PreRender();
    bool  PostRender();
    bool  Render();
    bool  Release();
};

