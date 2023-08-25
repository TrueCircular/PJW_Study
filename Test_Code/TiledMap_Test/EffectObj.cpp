#include "EffectObj.h"

void EffectObj::AddSpriteAddress(std::wstring address, int count)
{
	_begin = 0;
	_last = count;
	std::size_t found = address.find_last_of(L"/");
	std::wstring path = address.substr(0, found + 1);
	path += L"tile";

	for (int i = 0; i < count + 1; i++)
	{
		std::wstring temp = path;

		if (10 <= i && i < 100)
		{
			temp += L"0";
			temp += std::to_wstring(i);
			temp += L".png";
		}
		if (0 <= i && i < 10)
		{
			temp += L"00";
			temp += std::to_wstring(i);
			temp += L".png";

		}
		_spAdress.push_back(temp);
	}

	CreateSpriteList();

	_isSet = true;
}

void EffectObj::CreateSpriteList()
{
	if (_spAdress.size() <= 0)
		return;

	const TTexture* tex;

	for (auto a : _spAdress)
	{
		tex = I_Tex.Load(a);
		_spriteList.push_back(tex);
	}
}

bool EffectObj::Init(ID3D11Device* device, ID3D11DeviceContext* context, TVector3 pos, TVector3 scale)
{
	if (_isSet)
	{
		_effect = this;
		_effect->Set(device, context);
		_effect->SetPos(pos);
		_effect->SetScale(scale);
		_effect->Create(_spAdress[0], L"../../resource/shader/Plane.hlsl");
		return true;
	}

	return false;
}

bool EffectObj::CreateVertexBuffer()
{
	m_VertexList.resize(6);
	m_VertexList[0].t.x = 0.0f; m_VertexList[0].t.y = 0.0f;
	m_VertexList[1].t.x = 1.0f; m_VertexList[1].t.y = 0.0f;
	m_VertexList[2].t.x = 0.0f; m_VertexList[2].t.y = 1.0f;
	m_VertexList[3].t.x = 0.0f; m_VertexList[3].t.y = 1.0f;
	m_VertexList[4].t.x = 1.0f; m_VertexList[4].t.y = 0.0f;
	m_VertexList[5].t.x = 1.0f; m_VertexList[5].t.y = 1.0f;

	m_VertexList[0].p.x = -1.0f; m_VertexList[0].p.y = 1.0f;  m_VertexList[0].p.z = 0.0f;
	m_VertexList[1].p.x = 1.0f; m_VertexList[1].p.y = 1.0f;  m_VertexList[1].p.z = 0.0f;
	m_VertexList[2].p.x = -1.0f; m_VertexList[2].p.y = -1.0f;  m_VertexList[2].p.z = 0.0f;
	m_VertexList[3] = m_VertexList[2];
	m_VertexList[4] = m_VertexList[1];
	m_VertexList[5].p.x = 1.0f; m_VertexList[5].p.y = -1.0f;  m_VertexList[5].p.z = 0.0f;

	D3D11_BUFFER_DESC Desc;
	ZeroMemory(&Desc, sizeof(Desc));
	Desc.ByteWidth = sizeof(PT_Vertex) * m_VertexList.size();
	Desc.Usage = D3D11_USAGE_DEFAULT;
	Desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA InitialData;
	ZeroMemory(&InitialData, sizeof(InitialData));
	InitialData.pSysMem = &m_VertexList.at(0);

	HRESULT hr = m_pDevice->CreateBuffer(
		&Desc,
		&InitialData,
		&m_pVertexBuffer);
	if (FAILED(hr))
	{
		return false;
	}
	return true;
}

bool EffectObj::Frame()
{
	UpdateMatrix();

	return true;
}

bool EffectObj::Render()
{
	PreRender();
	indexTime += g_fSecondPerFrame;

	if (_isPlay)
	{
		if (indexTime < 0.04f)
		{
			if (_current > _last)
				_current = _begin;

			if (_current < _last)
			{
				_spriteList[_current]->Apply(m_pImmediateContext, 0);
			}
		}
		else
		{
			_current++;
			indexTime = 0;

		}



	}

	PostRender();
	return false;
}
