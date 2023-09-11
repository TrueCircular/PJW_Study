#include "TileManager.h"
#include "ICoreStd.h"
#include "TInput.h"

bool RectTile::CreateVertexBuffer()
{
	m_VertexList.resize(6);

	m_VertexList[0].c.x = 1.f; m_VertexList[0].c.y = 0.f; m_VertexList[0].c.z = 0.f;
	m_VertexList[0].c.w = 0.1f;
	m_VertexList[1].c.x = 1.f; m_VertexList[1].c.y = 0.f; m_VertexList[1].c.z = 0.f;
	m_VertexList[1].c.w = 0.1f;
	m_VertexList[2].c.x = 1.f; m_VertexList[2].c.y = 0.f; m_VertexList[2].c.z = 0.f;
	m_VertexList[2].c.w = 0.1f;
	m_VertexList[3].c.x = 1.f; m_VertexList[3].c.y = 0.f; m_VertexList[3].c.z = 0.f;
	m_VertexList[3].c.w = 0.1f;
	m_VertexList[4].c.x = 1.f; m_VertexList[4].c.y = 0.f; m_VertexList[4].c.z = 0.f;
	m_VertexList[4].c.w = 0.1f;
	m_VertexList[5].c.x = 1.f; m_VertexList[5].c.y = 0.f; m_VertexList[5].c.z = 0.f;
	m_VertexList[5].c.w = 0.1f;

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

bool RectTile::Create(S_TOBJECT_DESC oDesc)
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

void RectTile::RectInCheck()
{
	TVector2 mouse = I_Input.GetWorldPosVec2({ (float)g_dwWindowWidth, (float)g_dwWindowHeight }, ICore::g_pMainCamera->m_vCameraPos);

 	if (m_tRT.ToPoint(mouse))
	{
		if (I_Input.m_dwKeyState[VK_LBUTTON] >= KEY_PUSH)
		{
			_tileType = TileType::TILE_WALL;
		}
		if (I_Input.m_dwKeyState[VK_RBUTTON] >= KEY_PUSH)
		{
			_tileType = TileType::TILE_FLOOR;
		}
	}
	if (I_Input.m_dwKeyState[VK_NUMPAD6] == KEY_PUSH)
	{
		_tileType = TileType::TILE_FLOOR;
	}
}

bool RectTile::Init()
{
	return true;
}

bool RectTile::Frame()
{
	//UpdateMatrix();
	SetMatrix(nullptr, &ICore::g_pMainCamera->m_matView, &ICore::g_pMainCamera->m_matOrthoProjection);

	return true;
}

bool RectTile::PreRender()
{
	UpdateRect();
	RectInCheck();

	m_pImmediateContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);

	m_pImmediateContext->IASetInputLayout(m_pVertexLayout);

	switch (_tileType)
	{
	case TileType::TILE_FLOOR:
	{
		if (m_pShader != nullptr)
		{
			m_pShader->Apply(m_pImmediateContext, 1);
		}
		break;
	}
	case TileType::TILE_WALL:
	{
		if (m_pShader != nullptr)
		{
			m_pShader->Apply(m_pImmediateContext, 2);
		}
		break;
	}
	case TileType::TILE_POTAL:
	{
		if (m_pShader != nullptr)
		{
			m_pShader->Apply(m_pImmediateContext, 3);
		}
		break;
	}
	default:
		break;
	}


	UINT stride = sizeof(PT_Vertex);
	UINT offset = 0;

	m_pImmediateContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
	m_pImmediateContext->IASetPrimitiveTopology(
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	return true;
}

bool RectTile::Render()
{
	PreRender();
	PostRender();
	return true;
}

bool RectTile::PostRender()
{
	SetSamplerState();
	m_pImmediateContext->Draw(m_VertexList.size(), 0);
	return true;
}

bool RectTile::Release()
{
	TObject::Release();
	return true;
}

TileManager::~TileManager()
{
	Release();
}

void TileManager::CreateRectTileMap(TVector3 mapScale, int widthCount, int heightCount)
{
	if (_rectTileList.size() > 0)
	{
		Release();
	}

	int totalCount = widthCount * heightCount;

	_rectTileList.resize(totalCount);

	float mapStartX = -mapScale.x;
	float mapStartY = mapScale.y;

	float coordinatesX = mapScale.x *2/ widthCount;
	float coordinatesY = mapScale.y *2/ heightCount;

	int horizontal = 0;
	int vertical = 0;

	float startX = mapStartX + coordinatesX;
	float startY = mapStartY - coordinatesY;

	for (int i = 0; i < totalCount; i++)
	{
		_rectTileList[i] = new RectTile;

		S_TOBJECT_DESC temp;
		temp.pos.x = startX + ((coordinatesX * 2) * horizontal);
		temp.pos.y = startY - ((coordinatesY * 2) * vertical);
		temp.pos.z = 0.f;
		temp.scale.x = coordinatesX;
		temp.scale.y = coordinatesY;
		temp.scale.z = 1.f;
		temp.shaderFileName = L"../../resource/shader/Plane.hlsl";

		_rectTileList[i]->Create(temp);
		_tileIndexCount++;
		_rectTileList[i]->_tileIndex = _tileIndexCount;


		horizontal++;

		if (horizontal == widthCount / 2)
		{
			horizontal = 0;
			vertical++;
		};
	}

}

void TileManager::CreatePointTileMap(TVector3 mapScale, int widthCount, int heightCount)
{
	if (_pointTileList.size() > 0)
	{
		PointTileRelease();
	}

	int totalCount = widthCount * heightCount;

	_pointTileList.resize(totalCount);

	int mapStartX = -mapScale.x;
	int mapStartY = mapScale.y;

	_coordinateOffset.x = mapScale.x * 2 / widthCount;
	_coordinateOffset.y = mapScale.y * 2 / heightCount;

	int horizontal = 0;
	int vertical = 0;

	int startX = mapStartX + _coordinateOffset.x;
	int startY = mapStartY - _coordinateOffset.y;

	for (int i = 0; i < totalCount; i++)
	{
		PointTile tile;

		tile._tileCoordinates.x = startX + ((_coordinateOffset.x * 2) * horizontal);
		tile._tileCoordinates.y = startY - ((_coordinateOffset.y * 2) * vertical);
		_tileIndexCount++;
		tile._tileIndex = _tileIndexCount;
		_pointTileList[i] = tile;

		horizontal++;

		if (horizontal == widthCount / 2)
		{
			horizontal = 0;
			vertical++;
		};
	}
}

bool TileManager::SaveTileData()
{
	return false;
}

bool TileManager::LoadTileData(std::wstring lPath)
{
	return false;
}

void TileManager::Frame()
{
	for (int i = 0; i < _rectTileList.size(); i++)
	{
		_rectTileList[i]->Frame();
	}
}

void TileManager::RectTileRelease()
{
	for (int i = 0; i < _rectTileList.size(); i++)
	{
		if (_rectTileList[i]) _rectTileList[i]->Release();

		delete _rectTileList[i];
		_rectTileList[i] = nullptr;
	}
	_rectTileList.clear();
	_tileIndexCount = -1;
}
void TileManager::PointTileRelease()
{
	_pointTileList.clear();
	_tileIndexCount = -1;
	_coordinateOffset.x = 0;
	_coordinateOffset.y = 0;
}

void TileManager::Release()
{
}

void TileManager::Render()
{
	for (auto a : _rectTileList)
	{
		a->Render();
	}
}
