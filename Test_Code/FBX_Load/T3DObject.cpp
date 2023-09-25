#include "T3DObject.h"

void T3DObject::LoadTextureList(std::vector<W_STR> fileList)
{
    for (int i = 0; i < fileList.size(); i++)
    {
        const TTexture* temp = I_Tex.Load(fileList[i]);
        _texList.push_back(temp);
    }
}

bool T3DObject::Create(S_T3DOBJECT_DESC desc)
{
    CreateConstantBuffer();
    CreateVertexData();
    CreateIndexData();
    CreateVertexBuffer();
    CreateIndexBuffer();
    m_pShader = I_Shader.Load(desc._shaderPath);
    CreateInputLayout();
    m_pTex = I_Tex.Load(desc._texPath);

    SetPos(desc._pos);
    SetQuaternionRotation(desc._rot);
    SetScale(desc._scale);

    UpdateMatrix();

    return true;
}

void T3DObject::SetQuaternionRotation(TQuaternion& rot)
{
    m_qRotation = rot;
}

bool T3DObject::PostRender()
{
    for (int i = 0; i < _mesh->m_triangleList.size(); i++)
    {
        if (_texList.size() && _texList[i])
        {
            _texList[i]->Apply(m_pImmediateContext, 0);
        }
        if (m_pIndexBuffer == nullptr)
        {
            m_pImmediateContext->Draw(_mesh->m_triangleList[i].size(),
                                      _mesh->m_offsetList[i]);
        }
    }

    return true;
}

void T3DObject::UpdateMatrix()
{
    TMatrix scale, rotation, translate;

    D3DXMatrixScaling(&scale, m_vScale.x, m_vScale.y, m_vScale.z);
    D3DXMatrixRotationQuaternion(&rotation, &m_qRotation);
    D3DXMatrixTranslation(&translate, m_vPos.x, m_vPos.y, m_vPos.z);

    m_matWorld = scale * rotation * translate;
}
