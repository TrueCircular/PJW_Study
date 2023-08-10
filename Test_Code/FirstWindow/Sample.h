#pragma once
#include"TCore.h"

struct P3_VERTEX
{
    float x, y, z;
};

enum E_SHADER_LOAD_TYPE
{
    LOAD_VERTEX = 0,
    LOAD_PIXEL
};


class Sample : public TCore
{
public:
    ID3D11Buffer*       m_pVertexBuffer = nullptr;
    ID3D11InputLayout*  m_pVertexLayout = nullptr;
    ID3D11VertexShader* m_pVS = nullptr;
    ID3DBlob*           m_pVSBlob = nullptr;
    ID3D11PixelShader*  m_pPS = nullptr;
    ID3D11PixelShader*  m_pPS2 = nullptr;

private:
    bool LoadVertexShader();
    bool LoadPixelShader();
private:
    bool CreateVertexBuffer();
    bool LoadShader(E_SHADER_LOAD_TYPE eType);
    bool CreateVertexInputLayout();
public:
    bool Init() override;
    bool Frame() override;
    bool Render() override;
    bool Release() override;
};