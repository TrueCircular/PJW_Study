#pragma once
#include "TStd.h"
#include "GameObject.h"

namespace GameTile
{
	enum TileType
	{
		TILE_FLOOR,
		TILE_WALL,
		TILE_NONE
	};
}

class Tile :public TObject
{
	using TileType = GameTile::TileType;
public:
	UINT	 _tileIndex = -1;
	int		 _tileWidth = 0;
	int		 _tileHeight = 0;
	TileType _tileType = TileType::TILE_NONE;
public:
	bool  CreateVertexBuffer()override;
	bool  Create(std::wstring shaderFilename,std::wstring texFilename) override;
public:
	bool    Init() override;
	bool    Frame()override;
	bool    PreRender()override;
	bool    Render() {}
	bool    PostRender() {}
	bool    Release()override;
};


class TileManager
{
private:

private:
	TileManager() {}
public:
	~TileManager() {}
public:
	TileManager& GetInstance() { static TileManager ins; return ins; }
public:
	void CreateTileMap(TVector3 mapScale, int mapWidth, int mapHeight);
};

