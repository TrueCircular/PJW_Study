#include "..\WindowsProject1\Sample.h"
#include "Sample.h"


int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
    Sample mySample;
    mySample.SetRegisterClassWindow(hInstance);
    mySample.SetWindow(L"¹ÚÁø¿ø", 800, 600);
    mySample.Run();

    return 0;
}

bool Sample::CreateVertexBuffer()
{
    HRESULT hr = S_OK;
    P3_VERTEX vertices[] =
    {
        -1.0f,1.0f,0.5f,
        1.0f, 1.0f, 0.5f,
        -1.0f, -1.0f, 0.5f,
        1.0f, 1.0f, 0.5f,
        1.0f, -1.0f, 0.5f,
        -1.0f, -1.0f, 0.5f
    };
    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(P3_VERTEX) * 6;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA sd;
    ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
    sd.pSysMem = vertices;
    hr = m_pDevice->CreateBuffer(
        &bd, &sd, &m_pVertexBuffer
    );

    if (FAILED(hr))
        return false;

    return true;
}

bool Sample::LoadVertexShader()
{
    HRESULT hr = S_OK;
    ID3DBlob* vError = NULL;

    if (FAILED(hr = D3DCompileFromFile(
        L"VertexShader.vsh",
        nullptr,
        nullptr,
        "VS",
        "vs_5_0",
        0,
        0,
        &m_pVSBlob,
        &vError
    )))
    {
        if (vError) vError->Release();
        return false;
    }
    if (FAILED(hr = m_pDevice->CreateVertexShader(
        m_pVSBlob->GetBufferPointer(),
        m_pVSBlob->GetBufferSize(),
        nullptr,
        &m_pVS
    )))
    {
        if (vError) vError->Release();
        return false;
    }

    if (vError) vError->Release();

    return true;
}

bool Sample::LoadPixelShader()
{
    HRESULT hr = S_OK;
    ID3DBlob* vPixel = NULL;
    ID3DBlob* vError = NULL;

    if (FAILED(hr = D3DCompileFromFile(
        L"PixelShader.psh",
        nullptr,
        nullptr,
        "PS",
        "ps_5_0",
        0,
        0,
        &vPixel,
        &vError
    )))
    {
        return false;
    }
    if (FAILED(hr = m_pDevice->CreatePixelShader(
        vPixel->GetBufferPointer(),
        vPixel->GetBufferSize(),
        nullptr,
        &m_pPS
    )))
    {
        if (vPixel) vPixel->Release();
        if (vError) vError->Release();
        return false;
    }

    if (FAILED(hr = D3DCompileFromFile(
        L"PixelShader.psh",
        nullptr,
        nullptr,
        "PS2",
        "ps_5_0",
        0,
        0,
        &vPixel,
        &vError
    )))
    {
        return false;
    }
    if (FAILED(hr = m_pDevice->CreatePixelShader(
        vPixel->GetBufferPointer(),
        vPixel->GetBufferSize(),
        nullptr,
        &m_pPS2
    )))
    {
        if (vPixel) vPixel->Release();
        if (vError) vError->Release();
        return false;
    }

    if (vError) vError->Release();
    if (vPixel) vPixel->Release();

    return true;
}

bool Sample::CreateVertexInputLayout()
{
    HRESULT hr = S_OK;

    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
    };
    UINT iNumCount = sizeof(layout) / sizeof(layout[0]);

    hr = m_pDevice->CreateInputLayout(
        layout,
        iNumCount,
        m_pVSBlob->GetBufferPointer(),
        m_pVSBlob->GetBufferSize(),
        &m_pVertexLayout
    );

    if (FAILED(hr))
        return false;

    return true;
}

bool Sample::LoadShader(E_SHADER_LOAD_TYPE eType)
{
    switch (eType)
    {
    case E_SHADER_LOAD_TYPE::LOAD_VERTEX:
    {
        if (LoadVertexShader())
            return true;
    }
    case E_SHADER_LOAD_TYPE::LOAD_PIXEL:
    {
        if (LoadPixelShader())
            return true;
        break;
    }
    }
    return false;
}

bool Sample::Init()
{
    return false;
}

bool Sample::Frame()
{
    return true;
}

bool Sample::Render()
{ 
    m_pImmediateContext->IASetInputLayout(m_pVertexLayout);
    m_pImmediateContext->VSSetShader(m_pVS, NULL, 0);
    m_pImmediateContext->PSSetShader(m_pPS, NULL, 0);
    UINT stride = sizeof(P3_VERTEX);
    UINT offset = 0;
    m_pImmediateContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
    m_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    m_pImmediateContext->Draw(3, 0);

    m_pImmediateContext->PSSetShader(m_pPS2, NULL, 0);
    m_pImmediateContext->Draw(3, 3);

    return true;
}

bool Sample::Release()
{
    if (m_pVertexBuffer) m_pVertexBuffer->Release();
    if (m_pVertexLayout) m_pVertexLayout->Release();
    if (m_pVS) m_pVS->Release();
    if (m_pVSBlob) m_pVSBlob->Release();
    if (m_pPS) m_pPS->Release();

    m_pVertexBuffer = NULL;
    m_pVertexLayout = NULL;
    m_pVS = NULL;
    m_pVSBlob = NULL;
    m_pPS = NULL;

    return true;
}

