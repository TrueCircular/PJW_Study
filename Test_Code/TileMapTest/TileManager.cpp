#include "TileManager.h"
#include "ICoreStd.h"

bool Debug_Tile::CreateVertexBuffer()
{
	m_VertexList.resize(6);

	m_VertexList[0].c.x = 1.f; m_VertexList[0].c.y = 0.f; m_VertexList[0].c.z = 0.f;
	m_VertexList[0].c.w = 1.f;
	m_VertexList[1].c.x = 1.f; m_VertexList[1].c.y = 0.f; m_VertexList[1].c.z = 0.f;
	m_VertexList[1].c.w = 1.f;
	m_VertexList[2].c.x = 1.f; m_VertexList[2].c.y = 0.f; m_VertexList[2].c.z = 0.f;
	m_VertexList[2].c.w = 1.f;
	m_VertexList[3].c.x = 1.f; m_VertexList[3].c.y = 0.f; m_VertexList[3].c.z = 0.f;
	m_VertexList[3].c.w = 1.f;
	m_VertexList[4].c.x = 1.f; m_VertexList[4].c.y = 0.f; m_VertexList[4].c.z = 0.f;
	m_VertexList[4].c.w = 1.f;
	m_VertexList[5].c.x = 1.f; m_VertexList[5].c.y = 0.f; m_VertexList[5].c.z = 0.f;
	m_VertexList[5].c.w = 1.f;

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

bool Debug_Tile::Create(S_TOBJECT_DESC oDesc)
{
	Set(ICore::g_pDevice, ICore::g_pContext);
    CreateConstantBuffer();
    CreateVertexBuffer();
    m_pShader = I_Shader.Load(oDesc.shaderFileName);
    CreateInputLayout();
    SetPos(oDesc.pos);
    SetScale(oDesc.scale);
    TVector2 temp = { oDesc.pos.x, oDesc.pos.y };
    SetRect(temp, oDesc.scale.x * 2.0f, oDesc.scale.y * 2.0f);

    UpdateMatrix();
    return true;
}

void Debug_Tile::UpdateTile()
{
    SetMatrix(nullptr, &ICore::g_pMainCamera->m_matView, &ICore::g_pMainCamera->m_matOrthoProjection);

    m_pImmediateContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);

    m_pImmediateContext->IASetInputLayout(m_pVertexLayout);
    if (m_pShader != nullptr)
    {
        m_pShader->Apply(m_pImmediateContext, 1);
    }

    UINT stride = sizeof(PT_Vertex);
    UINT offset = 0;

    m_pImmediateContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
    m_pImmediateContext->IASetPrimitiveTopology(
        D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	SetSamplerState();
	m_pImmediateContext->Draw(m_VertexList.size(), 0);
}

bool Debug_Tile::Init()
{
    return true;
}

bool Debug_Tile::Frame()
{
    UpdateMatrix();
    UpdateRect();
    
    return true;
}

bool Debug_Tile::Render()
{
	UpdateTile();

    return true;
}

bool Debug_Tile::Release()
{
    TObject::Release();

    return true;
}

TileManager::~TileManager()
{
	DebugTileRelease();
}

void TileManager::CreateDebugTileMap(TVector3 mapScale, int widthCount, int heightCount)
{
	if (_debugTileList.size() > 0)
	{
		DebugTileRelease();
		_debugTileList.clear();
	}

	int totalCount = widthCount * heightCount;
	_debugTileList.resize(totalCount);

	float mapStartX = -mapScale.x;
	float mapStartY = mapScale.y;
	
	float coordinatesX = mapScale.x * 2 / widthCount;
	float coordinatesY = mapScale.y * 2 / heightCount;

	int horizontal = 1;
	int vertical = 1;

	for (int i = 0; i < totalCount; i++)
	{
		_debugTileList[i] = new Debug_Tile;

		S_TOBJECT_DESC temp;
		temp.pos.x = mapStartX + (coordinatesX * horizontal);
		temp.pos.y = mapStartY - (coordinatesY * vertical);
		temp.pos.z = 1.f;
		temp.scale.x = coordinatesX;
		temp.scale.y = coordinatesY;
		temp.shaderFileName = L"../../resource/shader/Plane.hlsl";
		_debugTileList[i]->Create(temp);
		_tileIndexCount++;
		_debugTileList[i]->_tileIndex = _tileIndexCount;

		horizontal++;
		if (horizontal >= widthCount)
		{
			horizontal = 1;
			vertical++;
		}
	}

}

void TileManager::CreateTileMap(TVector3 mapScale, int widthCount, int heightCount)
{
}

bool TileManager::SaveTileData()
{
    return false;
}

bool TileManager::LoadTileData(std::wstring lPath)
{
    return false;
}

void TileManager::DebugTileFrame()
{
	for (int i = 0; i < _debugTileList.size(); i++)
	{
		_debugTileList[i]->Frame();
	}
}

void TileManager::DebugTileRelease()
{
	for (int i = 0; i < _debugTileList.size(); i++)
	{
		if(_debugTileList[i]) _debugTileList[i]->Release();

		_debugTileList[i] = nullptr;
	}
}

void TileManager::DebugTileRender()
{
	for (int i = 0; i < _debugTileList.size(); i++)
	{
		_debugTileList[i]->Render();
	}
}
