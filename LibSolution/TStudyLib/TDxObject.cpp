#include "TDxObject.h"
void  TDxObject::Set(ID3D11Device* pDevice, ID3D11DeviceContext* pImmediateContext)
{
	m_pDevice = pDevice;
	m_pImmediateContext = pImmediateContext;
}
bool  TDxObject::CreateVertexBuffer()
{
	return true;
}
bool  TDxObject::CreateConstantBuffer()
{
	D3D11_BUFFER_DESC Desc;
	ZeroMemory(&Desc, sizeof(Desc));
	Desc.ByteWidth = sizeof(CB_Data);
	Desc.Usage = D3D11_USAGE_DEFAULT;
	Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	HRESULT hr = m_pDevice->CreateBuffer(
		&Desc,
		nullptr,
		&m_pConstantBuffer);
	if (FAILED(hr))
	{
		return false;
	}
	return true;
}
bool  TDxObject::CreateInputLayout()
{
	const D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POS",  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",  0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA  , 0 },
		{ "TEXTURE",  0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT,  D3D11_INPUT_PER_VERTEX_DATA, 0 },

	};
	UINT iNumCount = sizeof(layout) / sizeof(layout[0]);

	if (m_pShader)
	{
		HRESULT hr = m_pDevice->CreateInputLayout(
			layout,
			iNumCount,
			m_pShader->GetBufferPointer(),
			m_pShader->GetBufferSize(),
			&m_pVertexLayout);
		if (FAILED(hr))
		{
			return false;
		}
	}
	return true;
}

bool TDxObject::SetSamplerState()
{
	//if (m_SamplerState != nullptr) m_SamplerState->Release();

	D3D11_SAMPLER_DESC samDesc;
	ZeroMemory(&samDesc, sizeof(samDesc));

	samDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	//samDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;

	samDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	samDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	samDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;

	//samDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	//samDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	//samDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samDesc.MaxAnisotropy = 16;

	HRESULT hr = m_pDevice->CreateSamplerState(&samDesc, &m_SamplerState);

	if (SUCCEEDED(hr))
	{
		m_pImmediateContext->PSSetSamplers(0, 1, &m_SamplerState);
		return true;
	}

	return false;
}
bool  TDxObject::Init()
{
	return true;
}
bool  TDxObject::Frame()
{
	return true;
}
bool  TDxObject::PreRender()
{
	m_pImmediateContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);

	if (m_pTex != nullptr)
	{
		m_pTex->Apply(m_pImmediateContext, 0);
	}
	m_pImmediateContext->IASetInputLayout(m_pVertexLayout);
	if (m_pShader != nullptr)
	{
		m_pShader->Apply(m_pImmediateContext, 0);
	}

	UINT stride = sizeof(PT_Vertex);
	UINT offset = 0;

	m_pImmediateContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
	m_pImmediateContext->IASetPrimitiveTopology(
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//m_pImmediateContext->IASetPrimitiveTopology(
	//	D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

	return true;
}
bool  TDxObject::Render()
{
	PreRender();
	PostRender();
	return true;
}
bool  TDxObject::PostRender()
{

	SetSamplerState();
	m_pImmediateContext->Draw(m_VertexList.size(), 0);

	return true;
}
bool  TDxObject::Release()
{
	if (m_pVertexBuffer) m_pVertexBuffer->Release();
	if (m_pVertexLayout) m_pVertexLayout->Release();
	if (m_pConstantBuffer)m_pConstantBuffer->Release();
	return true;
}
