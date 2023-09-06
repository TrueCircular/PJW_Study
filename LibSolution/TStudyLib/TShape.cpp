#include "TShape.h"

bool TShape::Create(S_TOBJECT_DESC desc)
{
    CreateConstantBuffer();
    CreateVertexBuffer();
    m_pShader = I_Shader.Load(desc.shaderFileName);
    CreateInputLayout();

    SetPos(desc.pos);
    SetScale(desc.scale);

    UpdateMatrix();

    return false;
}
