#pragma once
#include"TCore.h"
#include<d3d11.h>
#pragma comment(lib, "d3d11.lib")

class Sample : public TCore
{
private:
    IDXGISwapChain*         m_pSwapChain = nullptr;
    ID3D11Device*           m_pDevice = nullptr;
    ID3D11DeviceContext*    m_pImmediateContext = nullptr;
    ID3D11RenderTargetView* m_pRenderTargetView = nullptr;
public:
    bool Init() override;
    bool Frame() override;
    bool Render() override;
    bool Release() override;
};