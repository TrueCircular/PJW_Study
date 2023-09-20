#pragma once
#include "TDevice.h"
#include "TTimer.h"
#include "TInput.h"
#include "TCamera.h"
#include "TWriter.h"
#include "TShaderMgr.h"
#include "TTextureMgr.h"

class TCore : public TDevice
{
public:
    TTimer                          m_GameTimer;   
    std::shared_ptr<TCamera>        m_pMainCamera=nullptr;
public:
    ComPtr<ID3D11BlendState>        m_AlphaBlend = nullptr;
    ComPtr<ID3D11SamplerState>      m_SamplerState = nullptr;
    //DepthStencil
    ComPtr<ID3D11DepthStencilState> m_pDepthStencilState;
    ComPtr<ID3D11DepthStencilState> m_pDepthStencilStateDisable;
    //Rasterizer
    ComPtr<ID3D11RasterizerState>   m_pRSWireFrame;
    ComPtr<ID3D11RasterizerState>   m_pRSSolid;
public:
    virtual bool  Init();
    virtual bool  Frame();
    virtual bool  Render();
    virtual bool  Release();
public:
    void  CreateBlendState();
    void  CreateSamplerState();
    void  CreateDepthStencilState();
    void  CreateRasterizerState();
public:
    void          ResizeDevice(UINT width, UINT height) override;
    virtual bool  DeleteDxResource();
    virtual bool  CreateDxResource();
private:
    virtual bool  EngineInit();
    virtual bool  EngineFrame();
    virtual bool  EngineRender();
    virtual bool  EngineRelease();
public:
    bool  Run();
};

