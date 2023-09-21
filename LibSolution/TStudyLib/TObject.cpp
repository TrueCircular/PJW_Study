#include "TObject.h"
#include "DirectXTex.h" // ±âÅ¸
#include "TShaderMgr.h"
#include "TTextureMgr.h"
void   TObject::SetRect(TVector2& c, float w, float h)
{
    m_tRT.Set(c, w, h);
}
void  TObject::SetPos(TVector3 p)
{
    m_vPos = p;
}
void  TObject::SetScale(TVector3 s)
{
    m_vScale = s;
}
void TObject::SetRotation(TVector3 r)
{
    m_vRotation = r;
}
void TObject::ZRotation(float rad)
{
    m_vRotation.z = rad;
}
void  TObject::SetMatrix(TMatrix* matWorld, TMatrix* matView, TMatrix* matProj)
{
    if (matWorld != nullptr)
    {
        m_matWorld = *matWorld;
    }
    if (matView != nullptr)
    {
        m_matView = *matView;
    }
    if (matProj != nullptr)
    {
        m_matProj = *matProj;
    }
    m_cbData.matWorld = m_matWorld.Transpose();
    m_cbData.matView = m_matView.Transpose();
    m_cbData.matProj = m_matProj.Transpose();
    m_pImmediateContext->UpdateSubresource(m_pConstantBuffer, 0, nullptr, &m_cbData, 0, 0);

}
bool  TObject::Create(std::wstring texFilename,
                      std::wstring shaderFilename)
{
    CreateConstantBuffer();
    CreateVertexData();
    CreateIndexData();
    CreateVertexBuffer();
    CreateIndexBuffer();
    m_pShader = I_Shader.Load(shaderFilename);
    CreateInputLayout();
    m_pTex = I_Tex.Load(texFilename);

    UpdateMatrix();
    return true;
}
bool TObject::Create(S_TOBJECT_DESC desc)
{
    CreateConstantBuffer();
    CreateVertexBuffer();
    m_pShader = I_Shader.Load(desc.shaderFileName);
    CreateInputLayout();
    m_pTex = I_Tex.Load(desc.texFileName);

    SetPos(desc.pos);
    SetScale(desc.scale);
    TVector2 temp = { desc.pos.x, desc.pos.y };
    SetRect(temp, desc.scale.x * 2.0f, desc.scale.y * 2.0f );

    UpdateMatrix();
    return false;
}
void TObject::UpdateMatrix()
{
    TMatrix matScale, matRotation, matTranslate;
    D3DXMatrixScaling(&matScale, m_vScale.x, m_vScale.y, m_vScale.z);
    //D3DXMatrixRotationZ(&matRotation, m_vRotation.z);
    D3DXMatrixRotationYawPitchRoll(&matRotation, m_vRotation.y, m_vRotation.x, m_vRotation.z);
    D3DXMatrixTranslation(&matTranslate, m_vPos.x, m_vPos.y, m_vPos.z);

    m_matWorld = matScale * matRotation * matTranslate;
}
void TObject::UpdateRect()
{
    m_rtPos.x = m_vPos.x;
    m_rtPos.y = m_vPos.y;

    m_tRT.Set(m_rtPos, m_vScale.x * 2.0f, m_vScale.y * 2.0f);
}
bool  TObject::Init()
{   
    TDxObject::Init();
    return true;
}
bool  TObject::Frame()
{
    TDxObject::Frame();
    return true;
}
bool  TObject::Render()
{
    TDxObject::Render();
    return true;
}
bool  TObject::Release()
{
    TDxObject::Release();
    return true;
}
TObject::TObject()
{
    m_vPos      = TVector3(0,0,0);
    m_vScale    = TVector3(1, 1, 1);
    m_vRotation = TVector3(0, 0, 0);
}
